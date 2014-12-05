#include "mm.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX_SEQ_SIZE TEST_SIZE
#define TEST_SIZE 10

int seq[MAX_SEQ_SIZE];

typedef struct mm_info{
	char *byte;
	int size;
}mm_info;

mm_info mm_tst[TEST_SIZE];


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
	void *real_ptr;

	for(i = 0; i < MAX_SEQ_SIZE; i++) {
		seq[i] = i;
	}

	mm_init();

	rand_seq(seq, TEST_SIZE);

	for(i = 0; i < TEST_SIZE; i++) {
		mm_tst[i].size = seq[i];
		mm_tst[i].byte = mm_malloc(seq[i]);
		if(mm_tst[i].byte == NULL) {
			printf("line: %d ;mm_malloc return NULL\n", __LINE__);
		};
		*(int *)mm_tst[i].byte = seq[i];
	}

	checkheap(1);

	rand_seq(seq, TEST_SIZE); 
	for(i = 0; i < TEST_SIZE/ 2; i++) 
	{ 
		mm_free(mm_tst[seq[i]].byte);
	}

	checkheap(1);

	rand_seq(seq, TEST_SIZE);

	for(i = 0; i < TEST_SIZE; i++) {
		mm_tst[seq[i]].size = 7 *seq[i];
		mm_tst[seq[i]].byte = mm_malloc(7 * seq[i]);
		if(mm_tst[seq[i]].byte == NULL) {
			printf("line: %d ;mm_malloc return NULL\n", __LINE__);
		};
		*(int *)mm_tst[seq[i]].byte = 7 * seq[i];
	}

	checkheap(1);

	for(i = 0; i < TEST_SIZE; i++) {
		num1 = mm_tst[seq[i]].size;
		num2 = *(int *)mm_tst[seq[i]].byte;
		if(num1 != num2) { printf("mm error!\n");
			return -1;
		}
	}

	real_ptr = (void *)mm_tst[0].byte;
	printf("before realloc: %p\n", real_ptr);
	real_ptr = mm_realloc(real_ptr, mm_tst[0].size + 100);
	printf("after realloc: %p\n", real_ptr);
	checkheap(1);


	printf("not find error!\n");

	return 0;
}
