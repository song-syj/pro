#include<iostream>
#include<stack>
#include<cstdlib>
#include<cstring>

using namespace std;

stack<char> stk;

int main()
{
	char str[101];
	char strbak[101];
	
	char p, q, r, s, t;
	char x, y, op; 
	int status, i;

	while(cin >> str ) {
		if(strcmp(str,"0") == 0)
			break;
		x = 1;
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
			
			stk.push(strbak[0]);
			i = 1;
			while(!stk.empty()) {
				if((x = stk.top()) > 1) {
					stk.push(strbak[i++]);
				} else {
					stk.pop();
					if(stk.empty())
						break;
					else if((y = stk.top()) <= 1) {
						stk.pop();
						op = stk.top();
						stk.pop();
						
						switch(op) {
						case 'K': x = y & x; break;
						case 'A': x = y | x; break;
						case 'C': x = !y | x; break;
						case 'E': x = y == x; break;
						default: cout << "error" << endl;
							exit(1);
						}
						
						stk.push(x);
					} else {
						if(y == 'N') {
							stk.pop();
							x = !x;
							stk.push(x);
						}else {
							stk.push(x);
							stk.push(strbak[i++]);
						}
					}
				}
			}
			
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
