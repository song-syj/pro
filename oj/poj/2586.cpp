#include<iostream>

using namespace std;

int main()
{
	int s, d;
	int val;
	while(cin >> s >> d) {
		if(4 * s < d) {
			val = 10 * s - 2* d;
		} else if(3 * s < 2 * d) {
			val = 8 * s - 4 * d; 
		} else if(2 * s < 3 * d) {
			val = 6 * s - 6 * d;
		} else if(s < 4 * d) {
			val = 3 * s - 9 * d;
		} else
			val = -1;

		if(val > 0)
			cout << val << endl;
		else
			cout << "Deficit" << endl;
	}
	
	return 0;
}
