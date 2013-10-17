#include<stdio.h>
#include"heapsort.h"
#include"quicksort.h"

int main(int argc,char* argv[])
{
//	int a[]={4,1,3,2,16,9,10,14,8,7};
	int a[]={14,189,90,2188,54,56,59,9999,199999,1};
	int i;
/*	HEAP* pHeap;
	pHeap=BuiltHeap(a,10);
	for(i=0;i<10;i++)
		printf("%d ",pHeap->pArray[i]);
	printf("\n");
	HeapSort(pHeap);
	for(i=0;i<10;i++)
		printf("%d ",pHeap->pArray[i]);
	printf("\n");
	FreeHeap(pHeap);
	*/
	RandomizedQuickSort(a,0,9);
	for(i=0;i<10;i++)
		printf("%d ",a[i]);
	putchar('\n');
	return 0;
}
