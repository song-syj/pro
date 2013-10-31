#include<stdio.h>
#define ROW 6
#define COL 6
int matrix_chain_order(int *p, int len, int m[][COL], int s[][COL])
{
	int n = len - 1;
	int i, j, k, l;
	int  q;

	for(i = 0; i < n; i++)
		m[i][i] = 0;

	for(l = 2; l < n+1; l++) {
		for(i = 0; i < n - l + 1; i++) {
			j = i + l - 1;
			m[i][j] = 0x7FFFFFFF;
			for(k = i; k < j; k++) {
				q = m[i][k] + m[k+1][j] + p[i] * p[k+1] * p[j+1];
				if(q < m[i][j]) {
					m[i][j] = q;
					s[i][j] = k;
				}
			}
		}
	}
	return m[n-1][n-1];
}

int print_optimal_parens(int (*s)[COL], int i, int j)
{
	if(i == j)
		printf("A%d", i);
	else {
		printf("(");
		print_optimal_parens(s, i, *(*(s+i)+j));
		print_optimal_parens(s, *(*(s+i)+j)+1, j);
		printf(")");
	}
}

int main(int argc, char *argv[])
{
	int p[7] = {30, 35, 15, 5, 10, 20, 25};
	int m[6][6] = {0};
	int s[6][6] = {0};

	matrix_chain_order(p, 7, m, s);
	print_optimal_parens(s, 0, 5);
	putchar('\n');
}

