#include<iostream>
#include<cstring>

char str[1000001];
using namespace std;

int main()
{
	unsigned long long result = 0;
	int len;
	
	while(cin >> str) {
		result = 0;
		len = strlen(str);
	
		for(int i = 0; i < len; i++) {
			result = result *31 + str[i];
		}
		
		cout << result << endl;
	}
	
	return 0;
}
