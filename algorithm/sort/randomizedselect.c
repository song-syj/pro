#include"quicksort.h"
#include"randomizedselect.h"


int RandomizedSelect(int array[],int start,int end,int i)
{
	int q;
	int k;
	if(start==end)
		return array[start];
	q=RandomizedPartition(array,start,end);
	k=q-start;
	if(k==i)
		return array[q];
	else if(i<k)
		return RandomizedSelect(array,start,q-1,i);
	else 
		return RandomizedSelect(array,q+1,end,i-k);
}
