int GetFirstK(int data[], int length, int k)
{
	if(data == NULL || length == 0)
		return -1;

	int start = 0;
	int end = length - 1;
	int midIndex = (start + end) / 2;

	while(start <= end) {
		if(data[midIndex] == k) {
			if((midIndex > 0 && data[midIndex - 1] != k) || midIndex == 0)
				return midIndex;
			else
				end = midIndex - 1;
		} else if(data[midIndex]> k) {
			end = midIndex - 1;
		}
		else {
			start = midIndex + 1;
		}
			
	}

	return -1;
}

int GetLastK(int data[], int length, int k)
{
	if(data == NULL || length == 0)
		return -1;

	int start = 0;
	int end = length - 1;
	int midIndex = (start + end) / 2;

	while(start <= end) {
		if(data[midIndex] == k) {
			if((midIndex < length - 1 && data[midIndex + 1] != k) || midIndex == length - 1)
				return midIndex;
			else
				start = midIndex + 1;
		} else if(data[midIndex]> k) {
			end = midIndex - 1;
		}
		else {
			start = midIndex + 1;
		}
			
	}

	return -1;
}

int GetNumberOfK(int data[], int length, int k)
{
	int number =  0;
	if(data != NULL && int length > 0) {
		int first = GetFirstK(data, length, k);
		int last = GetLastK(data, length, k);

		if(first != -1 && last != -1)
			number = last - first + 1;
	}

	return number;
}
