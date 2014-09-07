bool g_InvalidInput = false;

int FindGreatestSumOfSubArray(int *pData, in nLength)
{
	if(pData == || nLength <= 0) {
		g_InvalidInput = true;
		return 0;
	}

	int nCurrentSum = 0;
	int nGreatestSum = 0x80000000;
	for(int i = 0; i < nLength; i++) {
		if(nCurrentSum <= 0)
			nCurrentSum = pData[i]; 
		else 
			nCurrentSum += pData[i];
		if(nCurrentSum > nGreatestSum)
			nGreatestSum = nCurrentSum;
	}

	return nGreatestSum;
}

int NumberOfBetween1AndN(unsigned n)
{
	int Factor = 1;

	int nCurrentNumber;
	int nHigherNumber;
	int nLowerNumer;
	int count = 0;

	while(Factor <= n) {
		nCurrentNumber = n / Factor % 10;
		nHigherNumber = n / Factor / 10;
		nLowerNumer = n  % Factor;
		Factor *= 10;

		switch(nCurrentNumber) {
		case 0:
			count += Factor * nHigherNumber;
			break;
		case 1:
			count += Factor * nHigherNumber + nLowerNumer + 1;
			break;
		default:
			count += Factor * (nHigherNumber + 1);
		}
	}

	return count;
}
