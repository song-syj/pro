#include<stdio.h>
#define MAXLEN 500005

int data[MAXLEN];
int temp[MAXLEN];

long long sum = 0;

void
merge_sort(int data[], int start, int end)
{
	 int mid;
	 int i, j, k;
	 
	 if(start < end) {
		  mid = (start + end) >> 1;
		  merge_sort(data, start, mid);
		  merge_sort(data, mid+1, end);
		  
		  for(i = start, j = mid+1, k = start;
			  i <= mid && j <= end; ) {
			   if(data[i] <= data[j]) {
					temp[k++] = data[i++];
			   } else {
					temp[k++] = data[j++];
					sum += j - k;
			   }
		  }
	 
		  for(; i <= mid;) temp[k++] = data[i++];
		  for(; j <= end;) temp[k++] = data[j++];
		  for(k = k -1; k >= start; k--) data[k] = temp[k];

	 }
}

int main()
{
	 int n;
	 int i;
	 
	 while(scanf("%d", &n) == 1 && n) {
		  for(i = 0; i < n; i++)
			   scanf("%d", data+i);

		  sum = 0;
		  merge_sort(data, 0, n - 1);

		  printf("%lld\n", sum);
	 }
	 
	 return 0;
}
