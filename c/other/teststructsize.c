#include<stdio.h>

struct test_struct {
	int x;
	short y;
	char z;
	double w;
};
int main(void)
{
	printf("%d",sizeof(struct test_struct));
	return 0;
}
