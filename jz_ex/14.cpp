#include<iostream>
using namespace std;

void ReorderOddEven(int *pData, unsigned int length)
{
	if(pData == NULL || length == 0) return;

	int *pBegin = pData;
	int *pEnd = pData+length-1;

	while(pBegin < pEnd) {
		if((*pBegin &0x1) == 0 && (*pEnd & 0x1) == 1) {
			int tmp = *pBegin;
			*pBegin = *pEnd;
			*pEnd = tmp;
		}

		if((*pBegin & 0x1) == 1)
			pBegin++;
		if((*pEnd & 0x1) == 0)
			pEnd--;
	}
}

int main()
{
	int data [] = {4, 5,7, 9,0, -2, -7};
	int length = sizeof(data)/sizeof(int);
	ReorderOddEven(data, length);
	for(int i = 0; i < length; i++) {
		cout << data[i] << " ";
	}
	cout << endl;

	return 0;
}
