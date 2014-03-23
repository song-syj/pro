#include<stdio.h>
#include<string.h>
#define PRIMER 100001

struct node{
	 int *data;
	 struct node *next;
} *pnode,snow_node[100000], hashtable[100001];

int data[100000][6];

int getint();
int hashcode(int data[6]);
int compare(int first[6], int next[6]);

int main()
{
	 int n, nval;
	 int i, j;
	 int flag;
	 int *pdata;
	 
	 scanf("%d", &n);
	 flag = 1;
	 
	 for(i = 0; i < n; i++) {
		  for(j = 0; j < 6; j++)
			   data[i][j] = getint();

		  snow_node[i].data = data[i];
		  nval = hashcode(data[i]);
		  
		  if(hashtable[nval].next == NULL) {
			   hashtable[nval].next = snow_node+i;
		  }else {
			   pnode = hashtable[nval].next;
			   pdata = snow_node[i].data;
			   
			   do  {
					flag = compare(pnode->data, pdata);
					pnode = pnode->next;
			   }while(pnode && flag);
			   
			   if(flag == 0)
					break;
			   else {
					snow_node[i].next = hashtable[nval].next;
					hashtable[nval].next = snow_node+i;
			   }
					
		  }
	 }
	 
	 if(flag == 0)
		  printf("Twin snowflakes found.\n");
	 else {
		  printf("No two snowflakes are alike.\n");
	 }
	 
	 return 0;
}

int hashcode(int data[6])
{
	 int x, z, y;
	 
	 x = data[0] + data[2] + data[4];
	 y = data[1] + data[3] + data[5];
	 z = (x ^ y) % PRIMER;
	 
	 return z;
}

int compare(int first[6], int next[6])
{
	 int i, j;
	 int tmp[12];
	 for(i = 0; i < 6; i++) {
		  tmp[i] = tmp[6+i] = first[i];
	 }

	 for(i = 0; i < 6; i++) {
		  if(tmp[i] == next[0]) {
			   for(j = 1; j < 6 &&
						tmp[i+j] == next[j]; j++);
			   if(j == 6)
					return 0;
		  }
	 }
	 
	 for(i = 11; i >= 6; i--) {
		  if(tmp[i] == next[0]) {
			   for(j = 1; j < 6 &&
						tmp[i - j] == next[j]; j++);
			   if(j == 6)
					return 0;
		  }
	 }

	 return 1;
}

int getint()
{
	 char c;
	 int sum = 0;
	 c = getchar();
	 while(c < '0' || c > '9') c = getchar();
	 
	 do {
		  sum += sum * 10 + c - '0';
		  c = getchar();
	 } while(c <= '9' && c >= '0');

	 return sum;
}
