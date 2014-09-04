#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

void swap(int *x, int *y)
{
	if(x != y) {
		*x ^= *y;
		*y ^= *x;
		*x ^= *y;
	}
}

int Partition(int data[], int start, int end)
{
	if(start < 0 || end < 0 || end < start) {
		cerr << "Invalid Parameters" << endl;
		exit(1);
	}

	srand((unsigned int)time(0));
	int index = rand() % (end - start+1) + start;

	swap(data+index, data+end);
	int small = start - 1;
	for(index = start; index < end; index++) {
		if(data[index] < data[end]) {
			small++;
			swap(data+small, data+index);
		}
	}
	small++;
	swap(data+small, data+index);

	return small;
}

void QuickSort(int data[], int start, int end)
{
	if (start >= end)
		return;
	int mid = Partition(data, start, end);
	
	if(mid > start)
		QuickSort(data, start, mid-1);
	if(mid < end)
		QuickSort(data, mid+1, end);
}

void SortAges(int ages[], int length)
{
	if(ages == NULL || length <= 0)
		return; 

	static const int oldestAge = 99;

	int timesOfAge[oldestAge + 1];

	for(int i = 0; i <= oldestAge; i++)
		timesOfAge[i] = 0;
	for(int i = 0; i < length; i++) {
		int age = ages[i];
		if(age < 0 || age > oldestAge) {
			cerr << "Invail age" << endl;
			exit(1);
		}

		timesOfAge[age]++;
	}

	int index = 0;
	for(int i = 0; i <= oldestAge; i++) {
		while(timesOfAge[i]-- > 0) {
			ages[index++] = i;
		}
	}
}

int MinInorder(int array[], int start, int end)
{
	int min = array[start];
	for(int i = start+1; i <= end; i++) {
		if(array[i] < min)
			min = array[i];
	}

	return min;
}

int MinOfRotatingArray(int *array, int length)
{
	if(array == NULL || length <= 0) {
		cerr << "Invalid parameters" << endl;
		exit(1);
	}

	int first = 0;
	int last = length - 1;
	int mid = first;

	while(array[first] >= array[last]) {
		if(first+1 == last) {
			mid = last;
			break;
		}
		mid = (first + last) / 2;

		if(array[mid] == array[first] &&
				array[mid] == array[last])
			return MinInorder(array, first, last);

		if(array[mid] >= array[first]) {
			first = mid;
		} else if(array[mid] <= array[last]) {
			last = mid;
		}
	}

	return array[mid];
}

int main()
{
	int data[] = {3, 4, 5, 6, 7, 2}; 
	int result = MinOfRotatingArray(data, 6);

	cout << result << endl;

	return 0;
}
