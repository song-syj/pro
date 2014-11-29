#include<iostream> 
#include<memory>
#include<pthread.h>
#include<stdio.h>
#include"lock_free_stack.h"

using namespace std;

lock_free_stack<int> stk;

void * read_thread(void * param)
{
	shared_ptr<int> data;
	do {
	do {
		data = stk.pop();
	} while(!data);
	} while(1);


	//printf("read data : %d\n", *data);

	return nullptr;
}

void * write_thread(void *param)
{
	while(1)  {
		stk.push((int)param);
	}

	return nullptr;
}

int main()
{
	pthread_t tid;
	for(int i = 0; i < 100; i++) {
		int ret = pthread_create(&tid, NULL, read_thread, NULL);
		if(ret) {
			perror("read_thread");
			exit(-1);
		}
		pthread_detach(tid);
	}


	for(int i = 0; i < 100; i++) {
		int ret = pthread_create(&tid, NULL, write_thread, (void *)i);
		if(ret) {
			perror("write_thread");
			exit(-1);
		}
		pthread_detach(tid);
	}

	pthread_exit(0);

	return 0;
}

