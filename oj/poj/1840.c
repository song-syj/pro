
int cmp(void *x, void *y)
{
	 return *(int *)x - *(int *)y;
}
int cube[51];
int coef[5];

int main()
{
	 int i, j, k, l;
	 
	 for(i = 1; i <= 50; i++) {
		  cube[i] = i*i*i;
	 }

	 for(i = 0; i < 5; i++)
		  scanf("%d", coef+i);
	 
	 qsort(coef, sizeof(int), 5, cmp);
	 for()
	 
	 return 0;
}
