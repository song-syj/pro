#include <iostream>
#include <stack>

using namespace std;

char strf[1001], strl[1001], trace[2000];
char *psf, *psl, *ptr;

stack<char> stk;


void DFS()
{
	if (*psl == '\0') {
		for(char *p = trace; p != ptr; p++) {
			cout << *p << " ";
		}

		cout <<  endl;
	}
		
	if (*psf != '\0') {
		stk.push(*psf++);
		*ptr++ = 'i';

		DFS();

		stk.pop();
		psf--;
		ptr--;
	}

	if (!stk.empty()) {
		if (stk.top() == *psl) {
			stk.pop();
			*ptr++ = 'o';
			psl++;
			
			DFS();

			ptr--;
			psl--;
			stk.push(*psl);
			
		} 
	}
}
int main(void)
{
	while (cin >> strf >> strl) {
		psf = strf;
		psl = strl;
		ptr = trace;
		
		cout << "[" << endl;
		DFS();
		cout << "]" << endl;
	}
	return 0;
}
	
