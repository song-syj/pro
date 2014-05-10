#include <iostream>
#include <cstring>

using namespace std;

void encode(char *str, int len)
{
	for (int i = 0; i < len; i++) {
		if (*str == '_')
			*str = 0;
		else if (*str == '.')
			*str = 27;
		else
			*str = *str - 'a' + 1;

		str++;
	}

}
void decode(char *str, int len)
{
	for (int i = 0; i < len; i++) {
		if (*str == 0)
			*str = '_';
		else if (*str == 27)
			*str = '.';
		else
			*str = 'a' - 1 + *str;
		str++;
	}
}

void decryption(char *str, int n, int k)
{
	char *p;
	p = new char[n];
	for (int i = 0; i < n; i ++) {
		p[(k * i) % n] = (str[i] + i ) % 28;
	}

	for (int i = 0; i < n; i ++) {
		str[i] = p[i];
	}
	
	delete[] p;
}

void untwist(char *str, int n, int k)
{
	encode(str, n);
	decryption(str, n , k);
	decode(str, n);
}

int main(void)
{
	int k;
	char str[100];

    cin >> k;
	
	while (k != 0) {
		cin >> str;
		
		untwist(str, strlen(str), k);
		cout << str << endl;
		
		cin >> k;
	}
	
	return 0;
}
	
