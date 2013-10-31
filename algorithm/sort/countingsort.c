#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void CountingSort(int a[],int b[],int len,int k);
int main(int argc,char* argv[])
{
	int a[]={19,9,20,36,1,8,8,51,37};
	int b[9];
	int i;
	CountingSort(a,b,9,51);
	for(i=0;i<9;i++)
	{
		printf("%d ",b[i]);
	}
	printf("\n");
	return 0;
	
}
void CountingSort(int a[],int b[],int len,int k)
{
	int *c;
	int i;
	c=malloc(sizeof(int)*k);
	memset(c,0,k*sizeof(int));
	for(i=0;i<len;i++)
	{
		c[a[i]-1]++;
	}
	for(i=1;i<k;i++)
	{
		c[i]=c[i]+c[i-1];
	}
	for(i=0;i<len;i++)
	{
		b[c[a[i]-1]-1]=a[i];
		c[a[i]-1]--;
	}
	free(c);
}
