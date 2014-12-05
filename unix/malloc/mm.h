#ifndef _MM_H
#define _MM_H

#include<unistd.h>

int mm_init(void);
void mm_free(void *bp);
void *mm_malloc(size_t size);
void printblock(void *bp); 
void checkheap(int verbose);
void checkblock(void *bp);

#endif
