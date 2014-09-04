
long long Fibonacci(unsigned n)
{
	if(n < 2)
		return n;
	long long fibNMinusOne = 1;
	long long fibNMinusTwo = 0;
	long long fibN = 0;
	
	for(unsigned int i = 2; i <= n; i++) {
		fibN = fibNMinusOne + fibNMinusTwo;

		fibNMinusTwo = fibNMinusOne;
		fibNMinusOne = fibN;
	}

	return fibN;
}
