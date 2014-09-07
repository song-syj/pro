bool g_bInputInvaid = false;
bool CheckInvalidArray(int* numbers, int length)
{
	g_bInputInvalid = false;

	if(numbers == NULL || length == 0)
		g_bInputInvalid = true;

	return g_bInputInvalid;
}

bool CheckMoreThanHalf(int numbers[], int length, int result)
{
	int times = 0;
	for(int i = 0; i < length; i++) {
		if(numbers[i] == result)
			times++;
	}

	if(times * 2 < length) {
		g_bInputInvalid = true;
		return false;
	}
	else 
		return true;
}

int MoreThanHalfNum(int* numbers, int length)
{
	if(CheckInalidArray(numbers, length))
		return 0;
	int result = 0;
	int times = 0;
	for(int i = 0; i < length; i++) {
		if(times == 0) {
			result = numbers[i];
		} else if(numbers[i] == result) {
			times++;
		} else {
			times--;
		}
	}
	if(!CheckMoreThanHalf(numbers, length, result));

	return result;
}

