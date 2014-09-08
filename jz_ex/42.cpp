#include <iostream>
#include <string.h>
using namespace std;

void Reverse(char *pBegin, char *pEnd)
{
	if(pBegin == NULL || pEnd == NULL)
		return;

	while(pBegin < pEnd) {
		char tmp = *pBegin;
		*pBegin = *pEnd;
		*pEnd = tmp;

		pBegin++;
		pEnd--;
	}
}

char *ReverseSentence(char *pData)
{
	if(pData == NULL)
		return NULL;

	char *pBegin = pData;
	char *pEnd = pData;
	while(*pEnd!= '\0') {pEnd++;}
	pEnd--;
	
	Reverse(pBegin, pEnd);

	pBegin = pEnd = pData;
	while(*pBegin != '\0') {
		if(*pBegin == ' ') {
			pBegin++;
			pEnd++;
		} else if(*pEnd == ' ' || *pEnd == '\0') {
			Reverse(pBegin, pEnd-1);
			pBegin = pEnd;
		} else {
			pEnd++;
		}
	}

	return pData;
}

char* LeftRotateString(char* pStr, int n)
{
	if(pStr != NULL) {
		int nLength = strlen(pStr);
		int shift = n % nLength;

		Reverse(pStr, pStr+shift-1);
		Reverse(pStr+shift, pStr+nLength-1);
		Reverse(pStr, pStr+nLength-1);
	}
	return pStr;
}

int main()
{
	char str[] = "I am a student.";
	cout << LeftRotateString(str, 2) << endl;

	return 0;
}
