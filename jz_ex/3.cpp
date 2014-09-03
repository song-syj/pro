#include<iostream>

using namespace std;

bool FindInArray(int *matrix, int rows, int columns, int number)
{
	bool found = false;

	if(matrix != NULL && rows > 0 && columns > 0) {
		int i = 0;
		int j = columns - 1;

		while(i < rows && j >= 0) {
			if(matrix[i*columns+j] > number)
				j--;
			else if (matrix[i*columns+j] < number)
				i++;
			else {
				found = true;
				break;
			}
		}
	}

	return found;
}

int main()
{
	//int arr[10] = {1, 2, 8, 9};
	//int arr[10] = {1, 2, 8, 9};
	int arr[16] = {1, 2, 8, 9, 2, 4, 9 ,12};

	bool ret = FindInArray(arr, 2, 4, 4);

	if(ret == true)
		cout << "find!" << endl;
	else
		cout << "not find!" << endl;

	return 0;
}
