#include<iostream>

using namespace std;

int turn[16] = {0xC800,0xE400,0x7200,0x3100,0x8C80,0x4E40,0x2720,0x1310,0x08C8,0x04E4,0x0272,0x0131,0x008C,0x004E,0x0027,0x0013};
int grids; 
int mini;

void round(int n, int step)
{
	if(grids == 0xFFFF || grids == 0x0) {
		if (mini > step)
			mini = step;
		return ;
	}
	
	if (n >= 16)
		return;
		
	round(n + 1, step);
	grids ^= turn[n];
	round(n + 1, step + 1);
	grids ^= turn[n];
}

int main()
{
	char c;
	grids = 0;
	for(int i = 0; i < 4; i++) {
		for(int j = 0 ; j < 4; j++) {
			cin >>  c;
			grids <<= 1;
			if(c == 'b')
				grids += 1;
		}
	}

	mini =16 + 1;
	round(0, 0);

	if(mini <16 + 1)
		cout << mini << endl;
	else
		cout << "Impossible" << endl;
	
	return 0;
}
