#ifndef _MEMLIB_H
#define _MEMLIB_H

#define MAX_HEAP (100 * (1 << 20))

void mem_init(void);
void *mem_sbrk(int incr);

#endif
