#include<iostream>
using namespace std;

int InversePairsCore(int data[], int copy[], int start, int end)
{
	if(start == end) {
		copy[start] = data[start];
		return 0;
	}

	int mid = (start + end) / 2;
	int left = InversePairsCore(copy, data,start, mid);
	int right = InversePairsCore(copy, data, mid+1, end);
	
	int i = mid;
	int j = end;
	int indexCopy = end;
	int count = 0;

	while(i >= start && j >= mid + 1) {
		if(data[i] > data[j]) {
			count += j  - mid;
			copy[indexCopy--] = data[i--];
		} else {
			copy[indexCopy--] = data[j--];
		}
	}

	while(i >= start)
		copy[indexCopy--] = data[i--];
	while(j >= mid + 1)
		copy[indexCopy--] = data[j--];
	
	return count + left + right;
}

int InversePairs(int *data, int length)
{
	if(data == NULL || length <= 0)
		return 0;

	int *copy = new int[length];
	for(int i = 0; i < length; i++)
		copy[i] = data[i];

	int count =  InversePairsCore(data, copy, 0, length - 1);

	delete[] copy;

	return count;
}

int main()
{
	int data[] = {7, 5, 6, 4};
	cout << InversePairs(data, 4) << endl;
	for(int i = 0; i < 4; i++)
		cout << data[i] << endl;

	return 0;
}
