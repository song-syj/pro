#include<stdio.h>
#include<stdlib.h>
#include"randomizedselect.h"

int main(int argc,char* argv[])
{
	int i;
	int len;
	int k;
	int num_select;
	int* pArray;
	if(argc<2)
		fprintf(stderr,"Input a number for array building!\n");
	len=atoi(argv[1]);
	if(len<=0)
		fprintf(stderr,"Input a positive number\n");
	pArray=(int*)malloc(sizeof(int)*len);
	srand((unsigned int)time(0));
	for(i=0;i<len;i++){
		pArray[i]=rand()%100;
		printf("%d ",pArray[i]);
	}
	k=rand()%len;
	printf("\n");
	printf("k= %d\n",k);
	num_select=RandomizedSelect(pArray,0,len-1,k);
	printf("The selected number is %d .\n",num_select);
	free(pArray);
	return 0;
}
