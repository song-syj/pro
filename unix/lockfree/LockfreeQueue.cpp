#include "LockfreeQueue.h"

#define CAS __sync_bool_compare_and_swap

void LockFreeQueue::Enqueue(int new_value)
{
	Node *q = new Node(new_value);
	Node *p = tail;
	oldp = p;
	do {
		while(p->next) {
			p = p->next;
		}
	} while(!CAS(p->next, NULL, q));

	CAS(tail, p, q);
}

int LockFreeQueue::Dequeue()
{
	Node *p;
	do {
		p = head->next;
		if(p == NULL)
			return ERR_EMPTY_QUEUE;
	} while(!CAS(head->next, p, p->next));

	int value = p->value;
	 delete p;	

	 return value;
}
