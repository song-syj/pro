#ifndef _HEAP_SORT_H
#define _HEAP_SORT_H

#define Parent(i) (i>>1)
#define LeftChild(i) (i<<1)
#define RightChild(i) ((i<<1)+1)
typedef struct{
	int* pArray;
	int heapSize;
	int length;
}HEAP;

void swap(int *a,int *b);
void MaxHeapify(HEAP* pHeap,int i);
HEAP* BuiltHeap(int array[],int len);
void HeapSort(HEAP* pHeap);
void FreeHeap(HEAP* pHeap);

#endif
