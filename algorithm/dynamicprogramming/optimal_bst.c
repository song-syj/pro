#include<stdio.h>
#include<stdlib.h>

#define MAXN 100
#define INF 0x7FFFFFFF;

static double cost[MAXN+2][MAXN+1];
static double w[MAXN+2][MAXN+1];
static int root[MAXN+1][MAXN+1];

void optimal_bst(double *p, double *q, int n);
void print_optimal_bst(int i, int j);

int
main(int argc, char *argv[])
{
	double *ptr_probp;
	double *ptr_probq;
	int n;
	int i;
	n = argc/2 - 1;
	ptr_probp = (double *)malloc(sizeof(double)*(n+1));
	ptr_probq = (double *)malloc(sizeof(double)*(n+1));

	for(i = 0; i < n+1; i++) {
		ptr_probp[i] = atof(argv[i+1]);
	}

	for(i = 0; i < n+1; i++) {
		ptr_probq[i] = atof(argv[i+n+2]);
	}
	optimal_bst(ptr_probp, ptr_probq, n);
	print_optimal_bst(1, n);
	putchar('\n');
}

void 
optimal_bst(double *p, double *q, int n)
{
	int i, j, k, l;
	double tmp;
	// initate the cost array and w array
	for(i = 1; i <= n+1; i++) {
		cost[i][i-1] = q[i-1];
		w[i][i-1] = q[i-1];
	}

	for(l = 1; l <= n; l++) {
		for(i = 1; i <= n-l+1; i++) {
			j = i + l -1;
			cost[i][j] = INF; 
			w[i][j] = w[i][j-1] + p[j] + q[j];
			for( k = i; k <= j; k++) {
				tmp = cost[i][k-1] + cost[k+1][j] + w[i][j];
				if(tmp < cost[i][j]) {
					cost[i][j] = tmp;
					root[i][j] = k;
				}
			}
		}
	}
}

void
print_optimal_bst(int i, int j)
{
	if (i <= j) {
		printf("%d", root[i][j]);
		if (i < root[i][j] && root[i][j] < j) {
			printf("(");
			print_optimal_bst(i, root[i][j]-1);
			printf(",");
			print_optimal_bst(root[i][j]+1, j);
			printf(")");
		}
		else if (i < root[i][j]) {
			printf("(");
			print_optimal_bst(i, root[i][j]-1);
			printf(",");
			printf(")");
		}
		else if (root[i][j] < j) {
			printf("(");
			printf(",");
			print_optimal_bst(root[i][j]+1, j);
			printf(")");
		}
	}
}

