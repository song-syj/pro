#include<iostream>
#include<stack>

using namespace std;

stack<char> stk;


int iswff(char c) {
	if(str[i] == 'p' ||
	   str[i] == 'q' ||
	   str[i] == 'r' ||
	   str[i] == 's' ||
	   str[i] == 't') {
		
		return 1;
	} else
		return 0;
}

int main()
{
	char str[101];
	char p, q, r, s, t;
	char not, bl;
	int status, i,;

	while(cin >> str ) {
		if(strcmp(str,"0"))
			break;
		
		not = 0;
		for(status = 0; status < 32; status++) {
			p = (status & 0x10) >> 4;
			q = (status & 0x08) >> 3;
			r = (status & 0x04) >> 2;
			s = (status & 0x02) >> 1;
			t = (status & 0x01);

			stk.push(str[0]);
			i = 1;
			bl = 1;
			while(stk.empty()) {
				if(stk.top > 1) {
					if(iswff(str[i])) {
						stk
					}
				}
			}
		}
	}
	return 0; 
}
