#ifndef _LOCK_FREE_STACK_H
#define _LOCK_FREE_STACK_H

#include<atomic>
#include<memory>
#include"hazard.h"

template<typename T>
class lock_free_stack
{
private:
	struct node {
		std::shared_ptr<T> data;
		node *next;
		node(T const& data_)
			: data(std::make_shared<T>(data_)), next(nullptr)
		{}
	};

	std::atomic<node *> head;

public:
	void push(T const& data);
	std::shared_ptr<T> pop();
};

template<typename T>
void lock_free_stack<T>::push(T const& data)
{
	node *new_node = new node(data);
	new_node->next = head.load();

	while(!head.compare_exchange_weak(new_node->next, new_node));
}

template<typename T>
std::shared_ptr<T> lock_free_stack<T>::pop()
{
	std::atomic<void*>& hp = get_hazard_pointer_for_current_thread();
	node* old_head=head.load();

	do {
		node* temp;
		do {
			temp = old_head;
			hp.store(old_head);
			old_head = head.load();
		} while (temp != old_head);
	} while (old_head && !head.compare_exchange_strong(old_head, old_head->next));
	hp.store(nullptr);

	std::shared_ptr<T> res;
	if (old_head) {
		res.swap(old_head->data);
		if(outstanding_hazard_pointers_for(old_head)) {
			reclaim_later(old_head);
		} else {
			delete old_head;
		}
		delete_nodes_with_no_hazards();
	}

	return res;

}




#endif
