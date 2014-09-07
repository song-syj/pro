#include<stdio.h>
#include<iostream>

void PrintMatrixClockwisely(int **number, int columns, int rows)
{
	if(number == NULL
	   || columns == 0
	   || rows == 0)
		return;
	int (* data)[columns];
	data = (int (*)[columns])(number);

	for(int circle = 0; 2 * circle < columns && 2 * circle < rows; circle++) {
		int endX = columns - circle - 1;
		int endY = rows - circle - 1;
		for(int i = circle; i <= endX; i++)
			printf("%d ", data[circle][i]);
		
		if(endY > circle) {
			for(int j = circle+1; j <= endY; j++) {
				printf("%d ", data[j][endX]);
			}
		}
		if(endY > circle && endX > circle) {
			for(int j = endX-1; j >= circle ; j--) {
				printf("%d ", data[endY][j]);
			}
		}
		if(endY-1 > circle && endX > circle) {
			for(int j = endY-1; j > circle ; j--) {
				printf("%d ", data[j][circle]);
			}
		}
	}
}

int main()
{
	/*int data[4][4] = {
		{1, 2, 3, 4}, 
		{5, 6, 7, 8}, 
		{9, 10, 11, 12},
		{13, 14, 15, 16}
	};*/
	int data[3][4] = {
		{1, 2, 3, 4}, 
		{5, 6, 7, 8}, 
		{13, 14, 15, 16}
	};
	PrintMatrixClockwisely((int **)data, 4, 3);
	
	return 0;
}
