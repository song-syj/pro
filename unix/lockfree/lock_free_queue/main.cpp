#include "lock_free_queue.h"
#include<thread>
#include<algorithm>
#include<iostream>


lock_free_queue<int> lfq;
int output_data[200000];
std::atomic<bool> go(false);

void write_fun(int start, int end)
{	
	while(!go)
		std::this_thread::yield();

	for(int i = start; i != end; i++) {
		lfq.push(i);
	}
}

void read_fun(int start, int end) 
{
	while(!go)
		std::this_thread::yield();

	std::unique_ptr<int> ptr_data;
	for(int i = start; i < end; i++) {
		while(!(ptr_data = lfq.pop()));
		output_data[i] = *ptr_data;
	}
}

const int max_size = 100;
const int step = 20;

int main()
{
	std::thread t1[100];
	std::thread t2[100];

	for(int i = 0; i < max_size; i++) {
		t1[i] = std::thread(read_fun, i * step, (i+1) * step);
		t2[i] = std::thread(write_fun, i * step, (i+1) * step);
	}

	go = true;

	for(int i = 0; i < max_size; i++) {
		t1[i].join();
		t2[i].join();
	}


	//for(int i = 0; i < max_size * step; i++) {
	//	if(i != 0)
	//		std::cout << ", ";
	//	std::cout << output_data[i];
	//}
	std::cout << std::endl;

	std::sort(output_data, output_data+max_size*step, [](int x, int y){ return x < y;});
	for(int i = 0; i < max_size*step; i++) {
		if(i != 0)
			std::cout << ", ";
		std::cout << output_data[i];
	}

	std::cout << std::endl;
	std::cout << g_count << std::endl;

	return 0;
}
