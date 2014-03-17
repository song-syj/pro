#include <iostream>
#include <cstdio>

using namespace std;


int main()
{
	int r, s, t;
	for(int i = 0; i < 4; i++) {
		s = 0xF << (3 - i << 2);
		for(int j = 0; j < 4; j++) {
			t = 0x1 << 3 - j;
			r = 0;
			for(int k = 0; k < 4; k++)
				if (k != i)
					 r += t << (3 - k << 2);
			r += s;
			
			if(j == 3)
				printf("0x%04x\n", r);
			else
				printf("0x%04x, ", r);
		}
	}
			
	return 0;
}
