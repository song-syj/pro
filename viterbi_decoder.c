#include "viterbi_decoder.h"
#include <stdio.h>
#include <math.h>

#define MAXMETRIC 128
#define MAXINT 32767
//#define DEBUG
#define NORM

static int bin2dec(unsigned char *bin, char size);
static void dec2bin(int dec, char size , unsigned char *bin);
static int get_next_state(int curr_state, unsigned char input_bit, unsigned char *memory_content);
void 
viterbi_decoder(unsigned char g[][K], 
		unsigned int length, 
		unsigned char *encoder_vector, 
		unsigned char *decoder_vector)
{
	int input[STATE_SIZE][STATE_SIZE];
	int output[STATE_SIZE][2];
	int next_state[STATE_SIZE][2];

	unsigned char branch_output[2];
	unsigned char memory_content[K];
	double path_metric[STATE_SIZE][2];
	int state_tracks[STATE_SIZE][DEPTH_TRELLIS+1];
	int state_sequence[DEPTH_TRELLIS+1];
	
	unsigned int t;// the time
	int i, j, l, n, m, step, ptr_tracks,ptr_cycle, nxt_state;
	double min_metric , tmp;
	unsigned char pos,min_pos;// the position of min path_metric
	unsigned char remain_size;
	double branch_metric;
	n = 2;
	m = K  - 1;
	//initial path_metric 
	for(i = 0; i < STATE_SIZE; i++) {
		for(j = 0 ; j < STATE_SIZE; j++) {
			input[i][j] = 0;
		}
		for(j = 0 ; j < n; j++) {
			output[i][j] = 0;
		}

		for(j = 0; j <= DEPTH_TRELLIS; j++)
			state_tracks[i][j] = 0;

		path_metric[i][0] = 0.0;
		path_metric[i][1] = MAXINT;
	}
	//generate all possible state transition and the corresponding output
	for(i = 0; i < STATE_SIZE; i++) {
		for(j = 0; j < n; j++) {
			nxt_state = get_next_state(i, j, memory_content);
			input[i][nxt_state] = j;
			next_state[i][j] = nxt_state;
			
			branch_output[0] = 0;
			branch_output[1] = 0;
			for(l = 0; l < K; l++) {
				branch_output[0] ^= memory_content[l]&g[0][l];
				branch_output[1] ^= memory_content[l]&g[1][l];
			}
			output[i][j] = bin2dec(branch_output,2);
		}
	}
#ifdef DEBUG
	printf("next state :\n");
	for (i = 0; i <STATE_SIZE; i++) {
		for (j = 0; j < n; j++) {
			printf("%d + %d -> %d ", i, j, next_state[i][j]);
		}
		putchar('\n');
	}
	printf("input :\n");
	for (i = 0; i <STATE_SIZE; i++) {
		for (j =0; j < n; j++)
			printf("(%d -> %d : %d) ", i, next_state[i][j], input[i][next_state[i][j]]);
		putchar('\n');
	}
	printf("output :\n");
	for (i = 0; i <STATE_SIZE; i++) {
		for (j = 0; j < n; j++) {
			printf("(%d + %d : %d) ", i, j, output[i][j]);
		}
		putchar('\n');
	}

#endif
	//calcurate the path metric 
	length = length >> 1;
	for(t = 0; t < length; t++) {
		if (t <= m)
			step = 1 << (m - t);
		else
			step = 1;
		ptr_tracks = (t+1) % (DEPTH_TRELLIS + 1);
		if (t >= length - m)//for the last m bit;
			 remain_size = 1 << (length - t);
		else
			remain_size = STATE_SIZE;
		for(i = 0; i < remain_size; i += step) {
			for (l = 0; l < n; l++) {
				dec2bin(output[i][l], n, branch_output);
				branch_metric = 0;
				for(j = 0; j < n; j++) {
					branch_metric += abs(encoder_vector[t*2+j] - branch_output[j]);
				}
				if(path_metric[next_state[i][l]][1] > path_metric[i][0] + branch_metric) {
					path_metric[next_state[i][l]][1] = path_metric[i][0] + branch_metric;
					state_tracks[next_state[i][l]][ptr_tracks] = i;
				}
			}
		}

		for(i = 0; i < STATE_SIZE; i++) {
			path_metric[i][0] = path_metric[i][1];
			path_metric[i][1] = MAXINT;
		}
		//time > depth of trellis,  track back 
		if(t >= DEPTH_TRELLIS - 1) {
			// find the best rout
			min_metric = MAXINT;
			for(j = 0; j < STATE_SIZE/2; j++) {
				if (path_metric[j][0] > path_metric[STATE_SIZE - 1 - j][0]) {
					tmp = path_metric[j][0];
					pos = j;
				} else {
					tmp = path_metric[STATE_SIZE - 1][0];
					pos = STATE_SIZE - 1 - j;
				}
				if (tmp < min_metric) {
					min_metric = tmp;
					min_pos = pos;
				}
			}
#ifdef NORM
			if (min_metric > MAXMETRIC) {
				for(i = 0; i < STATE_SIZE; i++) {
					path_metric[i][0] = path_metric[i][0] - min_metric;
					if(path_metric[i][0] > MAXMETRIC)
						path_metric[i][0] = MAXMETRIC;
				}
			}
#endif
			//track back and recovery the state sequence
			state_sequence[DEPTH_TRELLIS] = min_pos;
			for(j = DEPTH_TRELLIS; j > 0; j--) {
				ptr_cycle = (ptr_tracks + j - DEPTH_TRELLIS);
				if(ptr_cycle < 0)
					ptr_cycle = ptr_cycle + DEPTH_TRELLIS + 1;
				state_sequence[j - 1] = state_tracks[state_sequence[j]][ptr_cycle];
			}
			//according to the state_sequence , recovery the input bit in the encoding process
			decoder_vector[t - DEPTH_TRELLIS + 1] = input[state_sequence[0]][state_sequence[1]];
		}

	}
	for(i = 1; i < DEPTH_TRELLIS - m; i++) {
		decoder_vector[length - DEPTH_TRELLIS + i] = input[state_sequence[i]][state_sequence[i + 1]];
	}

}

static int 
get_next_state(int curr_state, unsigned char input_bit, unsigned char *memory_content)
{
	int next_state;
	char i;
	unsigned char binary_state[K - 1];
	dec2bin(curr_state, K - 1, binary_state);
	memory_content[0] = input_bit;
	for(i = 1; i < K; i++)
		memory_content[i] = binary_state[i-1];
	for(i = 0; i < K - 1; i++)
		binary_state[i] = memory_content[i];
	next_state = bin2dec(binary_state, K-1);

	return next_state;
}

static void
dec2bin(int dec, char size , unsigned char *bin)
{
	char i;
	for (i = size - 1; i >= 0; i--) {
		bin[i] = dec & 0x01;
		dec = dec >> 1;
	}
}

static int 
bin2dec(unsigned char *bin, char size)
{
	int dec = 0;
	int i;
	for (i = 0; i < size; i++)
		dec = (dec << 1) + bin[i];
	return dec;
}
