#include<iostream>
#include<cstring>
#include<stack>
using namespace std;

typedef struct mahjong{
	char type;
	char num;
}mahjong;

stack<mahjong> stk;

int main()
{
	char str[100];
	char c;
	int i, len, num;
	int result = 0;
	mahjong m;
	while(cin >> str) {
		result = num = 0;
		len = strlen(str);
		for(i = 0; i < len; i++) {
			c = str[i];
			if(c == ',' || c == '.') {
				int size = stk.size();
				switch(size) {
				case 2:
					num++;break;
				case 3:
					mahjong a, b, c;
					a = stk.top();
					stk.pop();
					b = stk.top();
					stk.pop();
					c = stk.top();
					stk.pop();
					if(a.num == '3' && a.type == 'T'
						&& b.num == '2' && c.num == '1')
						result += 1;
					break;
				case 4:
					result += 2;break;
				default:break;
				}
				
				if(num == 7) result += 2;
				while(!stk.empty()) stk.pop();
			
			} 
			if(c == 'T' || c == 'D') {
				m.type = c;
				m.num = str[i-1];
				stk.push(m);
			}	
		
			if(c == '.')
				break;
		}

		cout << result << endl;
	}
	return 0;
}

















