#include<iostream>

using namespace std;

#define N 4
#define M (4*4)

char grids[N][N];
int mini;

void flip(int pos)
{
	int  px = pos / N;
	int  py = pos % N;

	if (px < N)
		grids[px][py] = !grids[px][py];
	if (px - 1 >= 0)
		grids[px - 1][py] = !grids[px - 1][py];
	if (px + 1 < N)
		grids[px + 1][py] = !grids[px + 1][py];
	if (py - 1 >= 0)
		grids[px][py - 1] = !grids[px][py - 1];
	if (py + 1 < N)
		grids[px][py + 1] = !grids[px][py + 1];
}

bool complete()
{
	int i,j;
	int sum = 0;
	
	for(i = 0; i < N; i++)
		for(j = 0 ; j < N; j++)
			sum += grids[i][j];
	
	if(sum % M)
		return false;
	else
		return true;

}
void round(int n, int step)
{
	if(complete()) {
		if (mini > step)
			mini = step;
		return ;
	}
	
	if (n >= M)
		return;
		
	round(n + 1, step);
	flip(n);	
	round(n + 1, step + 1);
	flip(n);
}

int main()
{
	char c;
	
	for(int i = 0; i < N; i++) {
		for(int j = 0 ; j < N; j++) {
			cin >>  c;
			if(c == 'b')
				grids[i][j] = 1;
			else
				grids[i][j] = 0;
		}
	}

	mini =M + 1;
	round(0, 0);

	if(mini <M + 1)
		cout << mini << endl;
	else
		cout << "Impossible" << endl;
	
	return 0;
}
