void Permulation(char *pStr)
{
	if(Str == NULL)
		return;
	Permulation(pStr, pStr);
}

void Permulation(char pStr, char *pBegin)
{
	if(*pBegin == '\0') {
		printf("%s\n", pStr);
		return;
	}

	for(char *pCh = pBegin; pCh != '\0';pCh++) {
		swap(pCh, pBegin);
		Permulation(pStr, pBegin+1);
		swap(pCh, pBegin);
	}
}

void swap(char *x, char*y)
{
	*x ^= *y;
	*y ^= *x;
	*x ^= *y;
}
