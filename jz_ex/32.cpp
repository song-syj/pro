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
