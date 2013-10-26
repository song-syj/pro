/*
 * prior_queue.h
 *
 *  Created on: Oct 23, 2013
 *      Author: song
 */

#ifndef PRIOR_QUEUE_H_
#define PRIOR_QUEUE_H_

#include "types.h"

#define PARENT(i) ((i - 1) >> 1)
#define LEFTCHILD(i) (((i + 1) << 1) - 1)
#define RIGHTCHILD(i) (((i + 1) << 1))
typedef char (*compare_node)(void *, void *);
typedef void (*swap_data)(void **, void **);

typedef struct prior_queue{
	Uint32 length;
	Uint32 size;
	void **ptr_node;

	compare_node compare;
	swap_data swap;

}prior_queue;

prior_queue * build_prior_queue(Uint32 length, compare_node compare, swap_data swap);
Bool insert_prior_queue(prior_queue *ptr_queue, void *key);
void *extract_head(prior_queue *ptr_queue);
void *get_head(prior_queue *ptr_queue);
void delete_prior_queue(prior_queue *ptr_queue);


#endif /* PRIOR_QUEUE_H_ */
