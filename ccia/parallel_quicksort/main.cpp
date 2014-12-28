#include "parallel_quicksort.h"
#include <stdlib.h>
#include <iostream>

int main()
{
	sorter<int> srt;
	std::list<int> data;

	for(int i =0; i < 300000; i++) {
		data.push_back(rand() % 100);
	}
	data = parallel_quick_sort(data);   
	std::for_each(data.begin(), data.end(), [](int n){ std::cout << n << " "; });
	std::cout << std::endl;

	return 0;
}
