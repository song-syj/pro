#include <iostream>

using namespace std;

unsigned int  turn[16] = {0xf888, 0xf444, 0xf222, 0xf111,
						  0x8f88, 0x4f44, 0x2f22, 0x1f11,
						  0x88f8, 0x44f4, 0x22f2, 0x11f1,
						  0x888f, 0x444f, 0x222f, 0x111f,
};

int bitcount(unsigned int n)
{
	int c;
	for(c = 0; n; c++)
		n &= n - 1;
	return c;
}

int main(void)
{
	char c;
	unsigned int res = 0;
	int n;
	int px, py;
	
	for(int i = 0; i < 16; i++) {
		cin >> c;
		if (c == '+')
			res ^= turn[i];
		}

	n = bitcount(res);
	cout << n << endl;
	
	for(int i = 0; i < 16; i++)
		if (res & 0x8000 >> i) {
			px = i / 4 + 1;
			py = i % 4 + 1;
			cout << px << " "
				 << py << endl;
		}

	return 0;
}
