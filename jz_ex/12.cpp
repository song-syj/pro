#include <iostream>
#include <stdio.h>

using namespace std;

void PrintNumber(char number[], int length)
{
	int firstNotZero = 0;
	while(firstNotZero < length && number[firstNotZero] == '0')
		firstNotZero++;
	for(int i = firstNotZero; i < length; i++) {
		printf("%c", number[i]);
	}

	printf("\t");
}

void Print1ToMaxofNDigitsRecursively(char number[], int start, int length)
{
	if(start == length) {
		PrintNumber(number, length);
		return;
	}

	for(int i = 0; i < 10; i++) {
		number[start] = i + '0';
		Print1ToMaxofNDigitsRecursively(number, start+1, length);
	}
}

void Print1ToMaxofNDigits(int n)
{
	if(n <=0)
		return;

	char *number = new char[n+1];
	number[n] = '\0';

	Print1ToMaxofNDigitsRecursively(number, 0, n);

	delete[] number;
}

int main()
{
	Print1ToMaxofNDigits(2);

	return 0;
}
