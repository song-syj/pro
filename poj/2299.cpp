#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;

const int maxlen = 500001;

typedef struct pos {
	int val;
	int order;
}pos;

pos data[maxlen];
int convert[maxlen];
int tree[maxlen];

int length;

int lowbit(int val)
{
	return val & (-val);
}

void update(int index, int val)
{
	for(int i = index; i <= length; i += lowbit(i)) {
		tree[i] += val;
	}
}

int getsum(int index)
{
	int sum = 0;
	
	for(int i = index; i > 0; i -= lowbit(i)) {
		sum += tree[i];
	}

	return sum;
}

int cmp(const void *data1, const void *data2)
{
	return ((pos *)data1)->val - ((pos *)data2)->val;
}

int main()
{
	while(scanf("%d", &length) == 1 && length) {
		
		for(int i = 1; i <= length; i++) {
			scanf("%d",&(data[i].val));
			data[i].order = i;
		}

		qsort(data+1, length, sizeof(pos), cmp);
		for(int i = 1; i <= length; i++) {
			convert[data[i].order] = i;
		}

		long long result = 0;
		memset(tree, 0, sizeof(tree));
		for(int i = 1; i <= length; i++) {
			update(convert[i],1);
			result += i - getsum(convert[i]);
		}

		cout << result << endl;
		
	}
	
	return 0;
}
