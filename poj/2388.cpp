#include<iostream>
#include<cstdlib>
using namespace std;

void swap(int *first, int *second)
{
	int tmp;
	tmp = *first;
	*first = *second;
	*second = tmp;
}

int partition(int *src, int start, int end)
{
	int i, j;
	int pivot;

	i = start-1;
	j = rand() % (end - start+1) + start;
	swap(src+j, src+end);
	pivot = src[end];
	
	for(j = start; j < end; j++) {
		if(src[j] < pivot) {
			swap(src+j, src+i+1);
			i++;
		}
	}
	swap(src+1+i, src+end);
	return i+1;
}

int select(int *src, int start, int end, int order)
{
	int q;

	if(start == end)
		return src[start];
	
	q = partition(src, start, end);

	if( q == order)
		return src[q];
	else if (q > order)
		return select(src, start, q - 1, order);
	else
		return select(src, q+1, end, order);
}

int data[10000];

int main()
{

	int n;
	int result;
	while(cin >> n) {
		for(int i = 0; i < n; i++) {
			cin >> data[i];
		}
		result = select(data, 0, n - 1, n/2);
		cout << result << endl;
	}
	
	return 0;
}
