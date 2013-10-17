#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void KmpMatcher(char* t,char* p);
int* ComputePrefix(char* p);


int main(int arc,char* arv[])
{
	char t[]="bbc abcdab abcdabcdabde";
	char p[]="abcdabd";
	KmpMatcher(t,p);
	return 0;
}


void KmpMatcher(char* t,char* p)
{
	int* w;
	int lent;
	int lenp;
	int i,q;
	lent=strlen(t);
	lenp=strlen(p);
	w=ComputePrefix(p);
	
	q=0;
	for(i=0;i<lent;i++)
	{
		while(q>0&&p[q]!=t[i])
		{
			q=w[q-1];
		}
		if(p[q]==t[i])
		{
			q++;
		}
		if(q==lenp)
		{
			printf("find string whith shift %d\n",i-lenp+1);
			q=w[q-1];
		}
	}

}

int* ComputePrefix(char* p)
{
	int len,k,q;
	int* w;
	len=strlen(p);
	w=malloc(sizeof(int)*len);
	w[0]=0;
	k=0;

	for(q=1;q<len;q++)
	{
		while(k>0&&p[k]!=p[q])
		{
			k=w[k-1];
		}
		if(p[k]==p[q])
			k++;
		w[q]=k;
	}
	return w;

}
