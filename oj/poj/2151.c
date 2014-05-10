#include<stdio.h>

double p[1001][31];
double f[1001][31][31];

int m, n, t;

int main()
{
	 int i, j, k;
	 double pp, qq, rr;
	 
	 while(scanf("%d %d %d", &m, &t, &n) == 3) {
		  if(m == 0 && t== 0 && n == 0)
			   return 0;
	 
		  for(i = 1; i <= t; i++)
			   for(j = 1; j <= m; j++)
					scanf("%lf", &p[i][j]);
		  
		  for(i = 1; i <= t; i++ ) {
			   f[i][0][0] = 1.0;
			   f[i][0][1] = 0;
			   rr = 1.0;
			   for(j = 1; j <= m; j++) {
					pp = p[i][j];
					qq = 1 - p[i][j];
					rr *= qq;
					
					f[i][j][0] = rr;
					for(k = 1; k <= j; k++)
						 f[i][j][k] = f[i][j-1][k-1]
							  * pp + f[i][j-1][k] * qq;
			   }
		  }
		  
		  pp = qq = 1.0;
		  for(i = 1; i <= t; i++) {
			   rr = 0.0;
			   for(k = 1; k < n; k++) {
					rr += f[i][m][k];
			   }
			   qq *= rr;
			   
			   for(; k <= m; k++) {
					rr += f[i][m][k];
			   }
			   pp *= rr;
		  }

	 
		  printf("%.3f\n", pp - qq);
	 }
	 return 0;
}
