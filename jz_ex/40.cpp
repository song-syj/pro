unsigned int FindFirstBitIs1(unsigned n)
{
	int result = n & (n - 1);	

	return result ^ (result >> 1);
}
void FindNumberAppearOnce(int data[], int length, int* num1, int* num2)
{
	if(data == NULL || length < 2)
		return;

	int result = 0;
	for(int i = 0; i < length; i++)
		result ^= data[i];

	unsigned int firstOf1Number = FindFirstBitIs1(result);
	*num1 = *num2 = 0;

	for(int i = 0; i < length ; i++) {
		if((data[i] & firstOf1Number))
			*num1 ^= data[i];
		else
			*num2 ^= data[i];
	}
}
