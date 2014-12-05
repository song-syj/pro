#include "memlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

static char *mem_heap = 0;
static char *mem_brk;
static char *mem_max_addr;

void mem_init(void)
{
	if(mem_heap == 0) {
		mem_heap = (char*)malloc(MAX_HEAP);
		mem_brk = mem_heap;
		mem_max_addr = (char *)(mem_heap + MAX_HEAP);
	}
}

void *mem_sbrk(int incr)
{
	char *old_brk = mem_brk;
	if(mem_heap == 0)
		 mem_init();
	
	if(incr < 0 || (mem_brk + incr) > mem_max_addr) {
		errno = ENOMEM;
		fprintf(stderr, "ERROR: mem_sbrk failed, Ran out of memory ..\n");

		return (void *)-1;
	}

	mem_brk += incr;

	return old_brk;
}
