/*
 * prior_queue.c
 *
 *  Created on: Oct 23, 2013
 *      Author: song
 */
#include "prior_queue.h"
#include <stdlib.h>


static void queueify(prior_queue *ptr_queue, Uint32 i) ;
static void queue_increase_key(prior_queue *ptr_queue, Uint32 num, void *key);
static void queue_decrease_key(prior_queue *ptr_queue, Uint32 num, void *key);

prior_queue *
build_prior_queue(Uint32 length, compare_node compare, swap_data swap)
{
	prior_queue *ptr_queue = (prior_queue *)malloc(sizeof(prior_queue));
	ptr_queue->ptr_node =(void**)malloc(sizeof(void*) * length);
	ptr_queue->compare = compare;
	ptr_queue->swap = swap;
	ptr_queue->length = length;
	ptr_queue->size = 0;

	return ptr_queue;

}
Bool
insert_prior_queue(prior_queue *ptr_queue, void *key)
{
	if(ptr_queue->length <= ptr_queue->size) {
		return 0;
	}
	queue_increase_key(ptr_queue, ptr_queue->size, key);
	ptr_queue->size ++;

	return 1;
}

void *
extract_head(prior_queue *ptr_queue)
{
	void *tmp;
	if(ptr_queue->size == 0)
		return NULL;
	tmp = ptr_queue->ptr_node[0];
	ptr_queue->size --;
	ptr_queue->ptr_node[0] = ptr_queue->ptr_node[ptr_queue->size];
	queueify(ptr_queue, 0);

	return tmp;
}
void *
get_head(prior_queue *ptr_queue)
{
	if(ptr_queue->size == 0)
		return NULL;
	return ptr_queue->ptr_node[0];
}
void
delete_prior_queue(prior_queue *ptr_queue)
{
	free(ptr_queue->ptr_node);
	free(ptr_queue);
}

static void
queue_increase_key(prior_queue *ptr_queue, Uint32 num, void *key) //turn up a data
{
	Int32 i, cmp = 0;
	ptr_queue->ptr_node[num] = key;
	if(num == 0)
		return;
	i = num;
	

	while(i > 0) {
		cmp = ptr_queue->compare(ptr_queue->ptr_node[PARENT(i)], ptr_queue->ptr_node[i]);
		if (cmp > 0) {
			ptr_queue->swap(ptr_queue->ptr_node+i, ptr_queue->ptr_node+PARENT(i));
			i = PARENT(i);
		} else
			break;
	}
}

static void
queue_decrease_key(prior_queue *ptr_queue, Uint32 num, void *key)  //turn down a data
{
	ptr_queue->ptr_node[num] = key;
	if(num >= ptr_queue->size - 1)
		return ;
	queueify(ptr_queue, num);
}

static void 
queueify(prior_queue *ptr_queue, Uint32 i) 
{
	Uint32 l, r, large;
	Int8 cmp;
	l = LEFTCHILD(i);
	r = RIGHTCHILD(i);
	large = i;
	
	if (l < ptr_queue->size) {
		cmp = ptr_queue->compare(ptr_queue->ptr_node[i], ptr_queue->ptr_node[l]);
		if(cmp > 0)
			large = l;
	}
	
	if (r < ptr_queue->size) {
		cmp = ptr_queue->compare(ptr_queue->ptr_node[large], ptr_queue->ptr_node[r]);
		if (cmp > 1)
			large = r;
	}
	if (large != i) {
		ptr_queue->swap(ptr_queue->ptr_node+i, ptr_queue->ptr_node+large);
		queueify(ptr_queue, large);
	}
}
/*swap two the value of two data
 * except that they are in same physical space
 * */


