#include"quicksort.h"
#include<stdlib.h>
void swap(int *a,int *b) {
	if(a!=b)
	{
		*a=*a^*b;
		*b=*a^*b;
		*a=*a^*b;
	}
}

int Partition(int array[],int left,int right)
{
	int i,j;
	int x;
	x=array[right];
	i=left-1;
	for(j=left;j<right;j++)
	{
		if(array[j]<x)
		{
			i++;
			swap(array+i,array+j);
		}
	}
	swap(array+i+1,array+right);
	return i+1;
}

int RandomizedPartition(int array[],int left,int right)
{
	int rd;
	srand((unsigned int)time(0));
	rd=rand()%(right-left+1)+left;
	swap(array+rd,array+right);
	return Partition(array,left,right);
}

void QuickSort(int array[],int start,int end)
{
	int q;
	if(start<end)
	{
		q=Partition(array,start,end);
		QuickSort(array,start,q-1);
		QuickSort(array,q+1,end);
	}
}

void RandomizedQuickSort(int array[],int start,int end)
{
	int q;
	if(start<end)
	{
		q=RandomizedPartition(array,start,end);
		RandomizedQuickSort(array,start,q-1);
		RandomizedQuickSort(array,q+1,end);
	}
}
