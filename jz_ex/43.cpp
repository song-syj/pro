#include<iostream>
#include<math.h>
using namespace std;

const int g_maxValue = 6;
void SumProbabilityOfDices(int number, int* pProbabilities);
void SumProbabilityOfDices(int original, int current, int value, int tempSum, int* pProbabilities);

void PrintProbability(int number)
{
	if(number < 1)
		return;

	int *pProbability = new int [g_maxValue * number+1];
	for(int i = 0; i <= g_maxValue * number; i++) {
		pProbability[i] = 0;
	}

	for(int i = 1; i <= g_maxValue; i++) {
		pProbability[i] = 1;
	}

	for(int k = 2; k <= number; k++) {
		for(int i = k * g_maxValue; i >= k; i--) {
			int sum = 0;
			for(int j = 1; j <= number && j <= i-k+1; j++) {
				sum += pProbability[i-j];
			}
			pProbability[i] = sum;
		}
	}

	double total = pow((double)g_maxValue, (double)number);
	double sum = 0;
	for(int i = number; i <= g_maxValue * number; i++) {
		double ratio = (double)pProbability[i] / total;
		printf("%d: %f\t%d\n", i , ratio, pProbability[i]);
		sum += pProbability[i];
	}

	delete[] pProbability;
	cout << sum << endl;
}
void PrintSumProbabilityOfDices_1(int number)
{
	if(number < 1)
		return;

	int maxSum = number * g_maxValue;
	int* pProbabilities = new int[maxSum - number + 1];
	for(int i = number; i <= maxSum; ++i)
		pProbabilities[i - number] = 0;

	SumProbabilityOfDices(number, pProbabilities);

	int total = pow((float)g_maxValue, number);
	for(int i = number; i <= maxSum; ++i)
	{
		float ratio = (float)pProbabilities[i - number] / total;
		printf("%d: %f\t%d\n", i, ratio, pProbabilities[i - number]);
	}

	delete[] pProbabilities;
}

void SumProbabilityOfDices(int number, int* pProbabilities)
{
	for(int i = 1; i <= g_maxValue; ++i)
		SumProbabilityOfDices(number, number, i, 0, pProbabilities);
}

void SumProbabilityOfDices(int original, int current, int value, int tempSum, int* pProbabilities)
{
	if(current == 1)
	{
		int sum = value + tempSum;
		pProbabilities[sum - original]++;
	}
	else
	{
		for(int i = 1; i <= g_maxValue; ++i)
		{
			int sum = value + tempSum;
			SumProbabilityOfDices(original, current - 1, i, sum, pProbabilities);
		}
	}
} 

void PrintSumProbabilityOfDices_2(int number)
{
    double* pProbabilities[2];
    pProbabilities[0] = new double[g_maxValue * number + 1];
    pProbabilities[1] = new double[g_maxValue * number + 1];
    for(int i = 0; i < g_maxValue * number + 1; ++i)
    {
        pProbabilities[0][i] = 0;
        pProbabilities[1][i] = 0;
    }
 
    int flag = 0;
    for (int i = 1; i <= g_maxValue; ++i)
        pProbabilities[flag][i] = 1;
      
    for (int k = 2; k <= number; ++k)
    {
        for (int i = k; i <= g_maxValue * k; ++i)
        {
            pProbabilities[1 - flag][i] = 0;
            for(int j = 1; j <= i && j <= g_maxValue; ++j)
                pProbabilities[1 - flag][i] += pProbabilities[flag][i - j];
        }
 
        flag = 1 - flag;
    }
 
    double total = pow((double)g_maxValue, number);
    for(int i = number; i <= g_maxValue * number; ++i)
    {
        double ratio = pProbabilities[flag][i] / total;
        printf("%d: %f\n", i, ratio);
    }
 
    delete[] pProbabilities[0];
    delete[] pProbabilities[1];
}

int main()
{
	PrintProbability(6);
	PrintSumProbabilityOfDices_1(6);

	return 0;
}
