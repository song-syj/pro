#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int * lcs_length(char *x, char *y);
void print_lcs(int *c, char *x, char *y, int i, int j);
int lcs_length_improve(char *x, char *y);

int 
main(int argc, char *argv[])
{
	char *str1 = "BDCABA";
	char *str2 = "ABCBDAB";

	int lenstr1 = strlen(str1);
	int lenstr2 = strlen(str2);
	int *common;//record the length of the LCS of two string
	int len_lcs;

	common = lcs_length(str1, str2);
	print_lcs(common, str1, str2, lenstr1, lenstr2);
	putchar('\n');
	len_lcs = lcs_length_improve(str1, str2);
	printf("the length of lcs : %d\n", len_lcs);
	
	free(common);
}
int *
lcs_length(char *x, char *y)
{
	int m = strlen(x) + 1;
	int n = strlen(y) + 1;
	int *c = (int *)malloc(sizeof(int)*m*n);
	int i, j;
	
	memset(c, 0, sizeof(int)*m*n);
	for(i = 1; i < m; i++) {
		for(j = 1; j < n; j++) {
			if(x[i-1] == y[j-1] )
				c[i*n+j] = c[(i-1)*n+(j-1)] + 1;
			else
				c[i*n+j] = c[(i-1)*n+j] > c[i*n+j-1]
					? c[(i-1)*n+j] : c[i*n+j-1] ;
		}
	}

	return c;
}

void 
print_lcs(int *c, char *x, char *y, int i, int j)
{
	int n = strlen(y) + 1;

	if(i == 0 || j == 0)
		return;
	else if(c[i*n+j] == c[i*n+j-1])
		print_lcs(c, x, y, i, j-1);
	else if(c[i*n+j] == c[(i-1)*n+j])
		print_lcs(c, x, y, i-1, j);
	else {
		print_lcs(c, x, y, i-1, j-1);
		putchar(x[i-1]);
	}
}


int
lcs_length_improve(char *x, char *y)
{
	int i, j;
	char *str_max, *str_min; 
	int len_max, len_min;
	int *ptr_com;
	int len_lcs;
	if(strlen(x) > strlen(y)) {
		len_max = strlen(x) + 1;
		len_min = strlen(y) + 1;
		str_max = x;
		str_min = y;
	} else {
		len_max = strlen(y) + 1;
		len_min = strlen(x) + 1;
		str_max = y;
		str_min = x;
	}
	ptr_com = (int *)malloc(sizeof(int)*len_min*2);
	memset(ptr_com, 0, sizeof(int)*len_min*2);

	for(i = 1; i < len_max; i++)
		for(j = 1; j < len_min; j++) {
			if(str_max[i-1] == str_min[j-1])
				ptr_com[len_min+j] = ptr_com[j-1] + 1;
			else
				ptr_com[len_min+j] = ptr_com[j] > ptr_com[len_min+j-1]
					? ptr_com[j]: ptr_com[len_min+j-1];
			memcpy(ptr_com, ptr_com+len_min,sizeof(int)*len_min);
		}
	len_lcs = ptr_com[len_min-1];
	free(ptr_com);

	return  len_lcs;
}

