#include<iostream>
using namespace std;

bool FindNumbersWithSum(int data[], int length, int sum, int* num1, int* num2)
{
	if(data == NULL || length <= 0 || num1 == NULL || num2 == NULL)
		return false; 
	bool found = false;
	int small = 0;
	int large = length - 1;

	while(small < large) {
		int currSum = data[small] + data[large];
		if(currSum == sum) {
			found = true;
			*num1 = data[small];
			*num2 = data[large];
			break;
		} else if(currSum > sum) {
			large--;
		} else {
			small++;
		}
	}

	return found;
}

void PrintContinueSequence(int small, int big)
{
	for(int i = small; i <= big; i++) {
		printf("%d ", i);
	}
	printf("\n");
}

void FindContinueSequence(int sum)
{
	if(sum < 3)
		return;

	int small = 1;
	int big = 2;
	int middle = (sum + 1) / 2;
	int currSum = small + big;

	while(small < middle) {
		if(currSum == sum) {
			PrintContinueSequence(small, big);
			currSum += ++big;
		} else if(currSum < sum) {
			currSum += ++big;
		} else {
			currSum -= small++;
		}
	}
}

int main()
{
	FindContinueSequence(15);
	return 0;
}
