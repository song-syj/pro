#ifndef _LOCKFREE_QUEUE_H
#define _LOCKFREE_QUEUE_H 

#define ERR_EMPTY_QUEUE -1


class LockFreeQueue {
public:
	LockFreeQueue() 
		:front_node(-1), head(&front_node), top(Node) {};
	void EnQueue(int new_value);
	int Dequeue();
private:
	struct Node {
		int value;
		struct Node *next;
		Node(int new_value)
			:value(new_value), next(NULL) {}
	};
	
	Node front_node;
	Node* head;
	Node* top;
};


#endif
