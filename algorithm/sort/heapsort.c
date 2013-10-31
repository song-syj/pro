#include<stdio.h>
#include"heapsort.h"
#include<stdlib.h>
#include<string.h>


void swap(int *a,int *b)
{
	*a=*a^*b;
	*b=*a^*b;
	*a=*a^*b;
}
void MaxHeapify(HEAP* pHeap,int i)
{
	int largest;
	int left;
	int right;
	if(i<=0||i>pHeap->heapSize)
	{
		printf("error heapify!\n");
		return;
	}
	left=LeftChild(i);
	right=RightChild(i);
	largest=i;
	if((left<=pHeap->heapSize)&&((pHeap->pArray[left-1])>(pHeap->pArray[largest-1])))
	{
		largest=left;
	}
	if((right<=pHeap->heapSize)&&((pHeap->pArray[right-1])>(pHeap->pArray[largest-1])))
	{
		largest=right;
	}
	if(i!=largest)
	{
		swap(pHeap->pArray+i-1,pHeap->pArray+largest-1);
		MaxHeapify(pHeap,largest);
	}
	
}

HEAP* BuiltHeap(int array[],int len)
{
	HEAP* pHeap;
	int i;
	pHeap=(HEAP*)malloc(sizeof(HEAP));
	pHeap->heapSize=pHeap->length=len;
	pHeap->pArray=(int*)malloc(sizeof(int)*len);
	memcpy(pHeap->pArray,array,len*sizeof(int));
	for(i=len/2;i>0;i--)
	{
		MaxHeapify(pHeap,i);
	}
	return pHeap;
}

void HeapSort(HEAP* pHeap)
{
	int i;
	for(i=pHeap->heapSize;i>1;i--)
	{
		swap(pHeap->pArray,pHeap->pArray+i-1);
		pHeap->heapSize--;
		MaxHeapify(pHeap,1);
	}
}

void FreeHeap(HEAP* pHeap)
{
	free(pHeap->pArray);
	free(pHeap);
}
