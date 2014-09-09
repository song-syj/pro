int compare(const void *arg1, const void *arg2)
{
	return *(int*)arg1 - *(int*)arg2;
}

bool IsContinous(int *numbers, int length)
{
	if(numbers == NULL || length <= 0)
		false;

	qsort(numbers, length, sizeof(int), compare);

	int numberOfZero = 0;
	int numberOfGap = 0;

	for(int i = 0; i < length && numbers[i] == 0) {
		numberOfZero++;
	}
	for(int j = i; j < length - 1;j++) {
		if(numbers[j] == numbers[j+1])
			return false;
		numberOfGap += numbers[j+1] - numbers[j] - 1;
	}

	return (numberOfZero >= numberOfGap);
}
