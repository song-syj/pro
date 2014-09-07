
bool VerifySquenceOfBST(int sequence[], int length)
{
	if(sequence == NULL || length <= 0)
		return 0;

	int rootValue = sequence[length-1];
	int i = 0;
	for(i = 0; i < length-1; i++) {
		if(sequence[i] > rootValue) {
			break;
		}
	}

	int j = i;
	for(; j < length-1; j++) {
		if(sequence[j] < rootValue)
			return false;
	}

	bool left = true;
	if(i > 0)
		left = VerifySquenceOfBST(sequence, i);
	bool right = true;
	if(i < length - 1)
		right = VerifySquenceOfBST(sequence+i, length - i - 1);
		
	return left && right
}
