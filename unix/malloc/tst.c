#include "mm.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int seq[100];

typedef struct mm_info{
	char *byte;
	int size;
}mm_info;

mm_info mm_tst[100];


void rand_seq(int *seq, int size)
{
	int i = 0;
	int k;
	int tmp;
	
	srand(time(0));
	for(i = 1; i < size; i++) {
		k = rand() % size;;		
		tmp = seq[0];
		seq[0] = seq[k];
		seq[k] = tmp;
	}
}

int main()
{
	int i;
	int num1, num2;
	for(i = 0; i < 100; i++) {
		seq[i] = i;
	}

	mm_init();

	rand_seq(seq, 100);

	for(i = 0; i < 100; i++) {
		mm_tst[i].size = seq[i];
		mm_tst[i].byte = mm_malloc(seq[i]);
		if(mm_tst[i].byte == NULL) {
			printf("line: %d ;mm_malloc return NULL\n", __LINE__);
		};
		*(int *)mm_tst[i].byte = seq[i];
	}

	//checkheap(1);

	rand_seq(seq, 100); 
	for(i = 0; i < 50; i++) 
	{ 
		mm_free(mm_tst[seq[i]].byte);
	}

	//checkheap(1);

	rand_seq(seq, 100);

	for(i = 0; i < 100; i++) {
		mm_tst[seq[i]].size = 7 *seq[i];
		mm_tst[seq[i]].byte = mm_malloc(7 * seq[i]);
		if(mm_tst[seq[i]].byte == NULL) {
			printf("line: %d ;mm_malloc return NULL\n", __LINE__);
		};
		*(int *)mm_tst[seq[i]].byte = 7 * seq[i];
	}

	checkheap(1);

	for(i = 0; i < 100; i++) {
		num1 = mm_tst[seq[i]].size;
		num2 = *(int *)mm_tst[seq[i]].byte;
		if(num1 != num2) { printf("mm error!\n");
			return -1;
		}
	}


	printf("not find error!\n");

	return 0;
}
