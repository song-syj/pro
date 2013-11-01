#ifndef VITERBI_H
#define VITERBI_H

#define K 5

#if K == 3
#define STATE_SIZE 4
#endif

#if K == 5
#define STATE_SIZE 16
#endif

#if K == 7
#define STATE_SIZE 64
#endif

#if K == 9
#define STATE_SIZE 128
#endif

#define DEPTH_TRELLIS (K*5)

#endif

/*
 * void viterbi_decoder(g,length,encoder,decoder_vector)
 * function:
 *		implement hard decision viterbi decoder	
 * input:
 * 		g - polynomial
 * 		length - the length of encoder vector
 * 		encoder_vector - the data thatneed to be decode
 * output:
 * 		decoder_vector - the decoded data
 * return:
 * 		void 
 * exception:
 *
 * */

void viterbi_decoder(unsigned char g[][K], unsigned int length, unsigned char *encoder_vector, unsigned char *decoder_vector);
