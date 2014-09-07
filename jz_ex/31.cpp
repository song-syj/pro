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

