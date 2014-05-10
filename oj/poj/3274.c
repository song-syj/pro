#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

#define PRIMER 100009
#define K 31

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

typedef struct node {
	 int *pdata;
	 int pos;
	 struct node *next;
}node;

node *hashtable[PRIMER];
node cow[PRIMER];
int data[PRIMER][K];
int n, k;

int hashcode(int key[])
{
	 int i;
	 int val = 0;
	 
	 for(i = 1; i < k; i++)
		  val += abs(key[i] - key[i-1]);

	 return val;
}



int
main(int ac, char *av[])
{

	 int i, j, val;
	 int offset, base, diff;
	 int max = 0;
	 node *pn;
/* 	 FILE *pf, *pout;   */

/* 	 pf = fopen("testdata.dat", "r"); */
/* //	 pout = fopen("accum.dat", "w");  	  */
/* 	 n = 5000;   */
/* 	 k = 10;   */

	 scanf("%d %d", &n, &k);
	 
	 memset(hashtable, 0, sizeof(hashtable));
	 memset(cow, 0, sizeof(cow));
	 
	 cow[0].pdata = data[0];
	 cow[0].pos = 0;
	 cow[0].next = NULL;
	 hashtable[0] = cow;
	 
	 for(i = 1; i <= n; i++) {
		  scanf("%d", &val); 
		  /* fscanf(pf, "%d", &val);  */
		  
		  for(j = 0; j < k; j++) {
			   data[i][j] = data[i-1][j] + (val & 0x1);
			   val >>= 1;
		  }
		  
		  val = hashcode(data[i]);
		  if(hashtable[val] == NULL) {
			   cow[i].pdata = data[i];
			   cow[i].pos = i;
			   cow[i].next = NULL;
			   hashtable[val] = cow + i;
		  } else {
			   pn = hashtable[val];
			   
			   while(pn) {
					base = data[i][0] - pn->pdata[0];
					
					for(j = 1; j < k; j++) {
						 offset = data[i][j] - pn->pdata[j];
						 if(offset != base)
							  break;
					}
					
					if(j == k) {
						 diff = i - pn->pos;
						 if(diff > max)
							  max = diff;
						 break;
					}
					
					pn = pn -> next;
			   }

			   if(pn == NULL) {
					
					cow[i].pdata = data[i];
					cow[i].pos = i;
					cow[i].next = hashtable[val];
					hashtable[val] = cow + i;
			   }
		  }
	 }

	 
	 
	 printf("%d\n", max); 

	 return 0;
}
