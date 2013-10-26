#include <stdio.h>
#include "types.h"
#include "prior_queue.h"

void swap(void **a, void **b);
Int8 compare(void *a, void *b);

int main(void)
{
	int testdata[100];
	prior_queue *ptr_que;

	int i, n;
	scanf_s("%d", &n);
	for(i = 0; i < n;i ++) {
		scanf("%d",testdata+i);
	}
	ptr_que = build_prior_queue(100, compare, swap);
	for(i = 0; i < n;i ++) {
		if( insert_prior_queue(ptr_que, (void *)(testdata+i)) == False)
			break;
	}
	while(ptr_que->size > 0)
		printf("%d ", *(int *)extract_head(ptr_que));
	delete_prior_queue(ptr_que);
	getchar();
}

Int8 compare(void *a, void *b)
{
	if (*(int*)a < *(int*)b)
		return -1;
	else if (*(int*)a > *(int*)b)
		return 1;
	else
		return 0;
}

void swap(void **a, void **b)
{
	int *tmp;
	tmp = *(int**)a;
	*(int **)a = *(int**)b;
	*(int**)b =tmp;
}