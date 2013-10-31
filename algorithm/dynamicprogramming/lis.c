#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 100

int lis_nlogn(int *seq, int len, int *inc_seq);
static int binary_search(int *p, int len, int key);

int main(int argc, char *argv[])
{
	int i;
	int lis_len;
	int seq[MAXSIZE];
	int inc_seq[MAXSIZE];

	for(i = 0; i< MAXSIZE && scanf("%d", seq+i) != EOF ; i++);
	lis_len = lis_nlogn(seq, i, inc_seq);
	for(i = 0; i < lis_len; i++)
		printf("%d ", inc_seq[i]);
	fprintf(stdout,"\n");
	return 0;
}

int 
lis_nlogn(int *seq, int len, int *inc_seq)
{
	int *L, *M, *prev;
	int i, pos, lis_len;

	L = (int *)malloc(sizeof(int)*len);
	M = (int *)malloc(sizeof(int)*len);
	prev = (int *)malloc(sizeof(int)*len);

	L[0] = *seq;
	M[0] = 0;
	prev[0] = -1;
	lis_len = 1;

	for(i = 1; i < len; i++) {
		pos = binary_search(L, lis_len, seq[i]);
		L[pos] = seq[i];
		M[pos] = i;
		if(pos > 0)
			prev[i] = M[pos-1];
		else
			prev[i] = -1;
		if(pos + 1 > lis_len)
			lis_len ++;
	}

	pos = M[lis_len-1];
	for(i = lis_len - 1; i >= 0; i--) {
		inc_seq[i] = seq[pos];
		pos = prev[pos];
	}

	free(L);
	free(M);
	free(prev);

	return lis_len;
}

static int
binary_search(int *p, int len, int key)
{
	int left = 0;
	int right = len - 1;
	int mid;

	while(left <= right) {
		mid = (left + right) >> 1;
		if(p[mid] < key)
			left = mid + 1;
		else
			right = mid -1;
	}

	return left;
}
