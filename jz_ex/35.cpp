#include<iostream>

using namespace std;

char FirstNotRepeatingChar(char *pString)
{
	if(pString == NULL) return '\0';

	const int tableSize = 26;
	unsigned int hashTalbe[talbeSize];
	for(int i = 0; i < talbeSize; i++)
		hashTalbe[i] = 0;

	for(int i = 0; pString[i] != '\0'; i++)
		hashTalbe[i]++;

	for(int i = 0; pString[i] != '\0'; i++)
		if(pString[i] == 1)
			return 'a'+i;

	return '\0';
}
