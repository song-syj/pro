#include<stdio.h>

struct test_struct {
	int x;
	short y;
	char z;
	double w;
};

/* 24 bytes in Windows  */
struct S1 {
	char i;
	char j;
	int t;
	double d;
	char c;
};

/* 16 bytes in windows*/
#pragma pack(2)
struct S2 {
	char i;
	char j;
	int t;
	double d;
	char c;
};
#pragma pack()

int main(void)
{
	printf("%d",sizeof(struct S1));
	return 0;
}
