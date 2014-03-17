#include<iostream>
#include<stack>
#include<cstdlib>
#include<cstring>

using namespace std;

stack<char> stk;
char str[101];
char strbak[101];
int n;

char tautology() {
	n++;
	
	switch(strbak[n]) {
	case 'K': return tautology() & tautology();
	case 'A': return tautology() | tautology();
	case 'C': return !tautology() | tautology();
	case 'E': return tautology() == tautology();
	case 'N': return !tautology();
	default: return strbak[n];
	}
}

int main()
{
	
	char p, q, r, s, t;
	char x;
	int status, i;

	while(cin >> str ) {
		if(strcmp(str,"0") == 0)
			break;

		for(status = 0; status < 32; status++) {
			p = (status & 0x10) >> 4;
			q = (status & 0x08) >> 3;
			r = (status & 0x04) >> 2;
			s = (status & 0x02) >> 1;
			t = (status & 0x01);

			for(i = 0; str[i] != '\0'; i++) {
				switch(str[i]) {
				case 'p': strbak[i] = p; break;
				case 'q': strbak[i] = q; break;
				case 'r': strbak[i] = r; break;
				case 's': strbak[i] = s; break;
				case 't': strbak[i] = t; break;
				default:strbak[i] = str[i];
				}
			}
			n = -1;
			x = tautology();
			
			if(x == 0)
				break;
		}
		if(x == 1)
			cout << "tautology" << endl;
		else
			cout << "not" << endl;
	}
	
	return 0; 
}
