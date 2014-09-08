#include<iostream>
using namespace std;


int Min(int a, int b, int c)
{
	int min;
	min = (a > b)?b:a;
	min = (min > c)?c:min;

	return min;
}

int GetUglyNumber_Solution(int index)
{
	if(index <= 0)
		return 0;

	int *pUglyNumber = new int[index];
	pUglyNumber[0] = 1;
	int nextUglyIndex = 1;
	int *pMultiply2 = pUglyNumber;
	int *pMultiply3 = pUglyNumber;
	int *pMultiply5 = pUglyNumber;

	while(nextUglyIndex < index) {
		pUglyNumber[nextUglyIndex] = Min(*pMultiply2 * 2, *pMultiply3 * 3, *pMultiply5 * 5);

		while(*pMultiply2 * 2 <= pUglyNumber[nextUglyIndex])
			pMultiply2++;
		while(*pMultiply3 * 3 <= pUglyNumber[nextUglyIndex])
			pMultiply3++;
		while(*pMultiply5 * 5 <= pUglyNumber[nextUglyIndex])
			pMultiply5++;

		nextUglyIndex++;
	}

	int ugly = pUglyNumber[index-1];
	delete[] pUglyNumber;

	return ugly;
}

int main()
{
	cout << GetUglyNumber_Solution(1500) << endl;

	return 0;
}

