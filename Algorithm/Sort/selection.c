#include<stdio.h>


void SelectSort(int array[],int left, int right);
int Selection(int array[],int left,int right,int r);
int Partition(int array[],int left,int right,int median);
int Selection(int array[],int left,int right,int r)
{
	int num_total;
	int num_5;
	int num_remain;
	int i,k;
	int tmp;
	int median;
	int q;

	if(left==right)
		return array[left];
	num_5=(right - left + 1) / 5;
	num_remain=(right - left + 1) % 5;
	num_total=num_5+(num_remain>0 ? 1: 0);
	
	for(i=0;i<num_5;i++)
	{
		SelectSort(array,left+i*5,left+i*5+4);	
	}
	
	for(i=0;i<num_5;i++)
	{
		tmp=array[left+5*i+2];	
		array[left+5*i+2]=array[left+i];
		array[left+i]=tmp;
	}
	if(num_remain>0)
	{
		SelectSort(array,left+5*num_5,left+5*num_5+num_remain-1);	
		tmp=array[left+5*num_5+(num_remain-1)/2];	
		array[left+5*num_5+(num_remain-1)/2]=array[left+num_5];
		array[left+num_5]=tmp;
	}
	median=Selection(array,left,left+num_total-1,(num_total+1)/2);
	q=Partition(array,left,right,median);
	k=q-left+1;
	if(k==r)
		return median;
	else if(r<k)
		return Selection(array,left,q-1,r);
	else
		return Selection(array,q+1,right,r-k);
}


int Partition(int array[],int left,int right,int median)
{
	int i,j;
	int p;
	int tmp;
	i=left-1;

	for(j=left;j<=right;j++)
	{
		if(array[j]<median)
		{
			tmp=array[++i];
			array[i]=array[j];
			array[j]=tmp;
		}
	}
	for(j=right;j>i;j--)
		if(array[j]==median)
		{
			tmp=array[++i];
			array[i]=array[j];
			array[j]=tmp;
			break;
		}
	return i;
}
void SelectSort(int array[],int left, int right)
{
	int i,j;
	int x;
	for(i=left+1;i<=right;i++)
	{
		x=array[i];
		for(j=i-1;j>=left;j--)
			if(array[j]>x)
				array[j+1]=array[j];
			else
				break;
		array[j+1]=x;
	}
}



int main(void)
{
	int i;
	int array[]={567,9,101,67,13,241,56,78,2,4,29};
	for(i=0;i<11;i++)
		printf("%d :%d \n",i+1,Selection(array,0,10,i+1));
}
