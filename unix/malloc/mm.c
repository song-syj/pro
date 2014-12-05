#include <stddef.h>
#include<string.h>
#include <stdio.h>
#include "memlib.h"
#include "mm.h"

#define WSIZE 4
#define DSIZE 8
#define ALIGNMENT 8
#define ALIGN_MASK (ALIGNMENT - 1)

#define CHUNKSIZE (1 << 12)

#define MAX(x, y) ((x) > (y) ? (x) : (y))

#define PACK(size, alloc) (size | alloc)

#define GET(p)		(*(unsigned int *)(p))
#define PUT(p, val)	(*(unsigned int *)(p) = (val))

#define GET_SIZE(p)	(GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p) & 0x1)

#define HDRP(bp) 	((char *)(bp) - WSIZE)
#define FTRP(bp)	((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

#define NEXT_BLKP(bp) ((char *)(bp) + GET_SIZE(HDRP(bp)))
#define PREV_BLKP(bp) ((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE)))


#define NEXT_FIT

#ifdef NEXT_FIT
static char *rover;
#endif

static char *heap_listp = 0;

static void * extend_heap(size_t words);
static void *coalesce(void *bp);
static void * find_fit(size_t asize);
static void place(void *bp, size_t asize);
//static void printblock(void *bp); 
//static void checkheap(int verbose);
//static void checkblock(void *bp);

int mm_init(void)
{
	mem_init();

	if((heap_listp = mem_sbrk(4 * WSIZE)) == (void *)-1)
		return -1;

	PUT(heap_listp, 0);
	PUT(heap_listp + (1 * WSIZE), PACK(DSIZE, 1));
	PUT(heap_listp + (2 * WSIZE), PACK(DSIZE, 1));
	PUT(heap_listp + (3 * WSIZE), PACK(0, 1));
	heap_listp += 2 * WSIZE;

#ifdef NEXT_FIT
	rover = heap_listp;
#endif

	if(extend_heap(CHUNKSIZE / WSIZE) == NULL) {
		return -1;
	}

	return 0;
}

static void * extend_heap(size_t words)
{
	void *bp;
	size_t size;

	size = (words & 0x1) ? (words + 1) * WSIZE : (words) * WSIZE;
	
	if((long)(bp = mem_sbrk(size)) == -1)
		return NULL;

	PUT(HDRP(bp), PACK(size, 0));
	PUT(FTRP(bp), PACK(size, 0));
	PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1));

	return coalesce(bp);
}

static void *coalesce(void *bp)
{
	size_t prev_alloc = GET_ALLOC(FTRP((PREV_BLKP(bp))));
	size_t next_alloc = GET_ALLOC(HDRP((NEXT_BLKP(bp))));

	size_t size = GET_SIZE(HDRP(bp));

	if(prev_alloc && next_alloc) {
		return bp;
	} else if(!prev_alloc && next_alloc) {
		bp = PREV_BLKP(bp);
		size += GET_SIZE(HDRP(bp));
		PUT(HDRP(bp), PACK(size, 0));
		PUT(FTRP(bp), PACK(size, 0));
	} else if(prev_alloc && !next_alloc) {
		size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
		PUT(HDRP(bp), PACK(size, 0));
		PUT(FTRP(bp), PACK(size, 0));
	} else {
		size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
		bp = PREV_BLKP(bp);
		size += GET_SIZE(HDRP(bp));
		PUT(HDRP(bp), PACK(size, 0));
		PUT(FTRP(bp), PACK(size, 0));
	}

#ifdef NEXT_FIT
	if(rover > (char *)bp && rover < NEXT_BLKP(bp))
		rover = (char *)bp;
#endif
	
	return bp;
}


void mm_free(void *bp)
{
	if(heap_listp == 0)
		mm_init();
	size_t size = GET_SIZE(HDRP(bp));
	PUT(HDRP(bp), PACK(size, 0));
	PUT(FTRP(bp), PACK(size, 0));
	coalesce(bp);
}

void *mm_malloc(size_t size)
{
	size_t asize; /* Adjusted block size */
	size_t extendsize;
	char *bp;

	if(heap_listp == 0)
		mm_init();

	if(size <= DSIZE)
		 asize = 2 * DSIZE;
	else 
		asize = DSIZE * ((size +  DSIZE + (DSIZE - 1)) / DSIZE); // asize is the size of block

	if((bp = find_fit(asize)) != NULL) {
		place(bp, asize);

		return bp;
	}

	extendsize = MAX(asize, CHUNKSIZE);
	if((bp = extend_heap(extendsize)) != NULL) {
		place(bp, asize);
	} 

	return bp;
}

void *mm_realloc(void *bp, size_t size)
{
	size_t old_size;
	void *new_bp;

	if(size == 0) {
		mm_free(bp);
		return NULL;
	}

	if(bp == NULL) {
		return mm_malloc(size);
	}

	new_bp = mm_malloc(size);

	if(new_bp == NULL) {
		return NULL;
	}

	old_size = GET_SIZE(HDRP(bp));
	if(old_size > size) old_size = size;
	memcpy(new_bp, bp, old_size);

	mm_free(bp);

	return new_bp;
}

static void * find_fit(size_t asize)
{
	size_t size;

#ifdef NEXT_FIT
	char *old_rover = rover;
	for(; (size = GET_SIZE(HDRP(rover))) > 0; rover = NEXT_BLKP(rover)) {
		if(size >= asize && !GET_ALLOC(HDRP(rover))) {
			return rover;
		}
	}

	for(rover = heap_listp; rover < old_rover ; rover = NEXT_BLKP(rover)) {
		if(size >= asize && !GET_ALLOC(HDRP(rover))) {
			return rover;
		}
	}
	
#else
	void *bp;

	for(bp = heap_listp; (size = GET_SIZE((HDRP(bp)))); bp = NEXT_BLKP(bp)) {
		if(size >= asize && !GET_ALLOC(HDRP(bp))) {
			return bp;
		}
	}
#endif

	return NULL;
}

static void place(void *bp, size_t asize)
{
	size_t size;

	size = GET_SIZE(HDRP(bp));
	if(size - asize >= 2 * DSIZE) {
		PUT(HDRP(bp), PACK(asize, 1));
		PUT(FTRP(bp), PACK(asize, 1));
		bp = NEXT_BLKP(bp);
		PUT(HDRP(bp), PACK((size-asize), 0));
		PUT(FTRP(bp), PACK((size-asize), 0));
	} else {
		PUT(HDRP(bp), PACK(size, 1));
		PUT(FTRP(bp), PACK(size, 1));
	}
}

void printblock(void *bp) 
{
	size_t hsize, halloc, fsize, falloc;

	checkheap(0);
	hsize = GET_SIZE(HDRP(bp));
	halloc = GET_ALLOC(HDRP(bp));  
	fsize = GET_SIZE(FTRP(bp));
	falloc = GET_ALLOC(FTRP(bp));  

	if (hsize == 0) {
		printf("%p: EOL\n", bp);
		return;
	}

	 printf("%p: header: [%d:%c] footer: [%d:%c]\n", bp, 
	  	hsize, (halloc ? 'a' : 'f'), 
	  		fsize, (falloc ? 'a' : 'f')); 
}

void checkblock(void *bp) 
{
	if ((size_t)bp % 8)
		printf("Error: %p is not doubleword aligned\n", bp);
	if (GET(HDRP(bp)) != GET(FTRP(bp)))
		printf("Error: header does not match footer\n");
}

/* 
 *  * checkheap - Minimal check of the heap for consistency 
 *   */
void checkheap(int verbose) 
{
	char *bp = heap_listp;

	if (verbose)
		printf("Heap (%p):\n", heap_listp);

	if ((GET_SIZE(HDRP(heap_listp)) != DSIZE) || !GET_ALLOC(HDRP(heap_listp)))
		printf("Bad prologue header\n");
	checkblock(heap_listp);

	for (bp = heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp)) {
		if (verbose) 
			printblock(bp);
		checkblock(bp);
	}

	if (verbose)
		printblock(bp);
	if ((GET_SIZE(HDRP(bp)) != 0) || !(GET_ALLOC(HDRP(bp))))
		printf("Bad epilogue header\n");
}
