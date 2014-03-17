#include<iostream>

using namespace std;

int pseq[20];
int diff[20];
int wseq[20];

int main()
{
	int i, j, k;
	int n,len, prev, curr;
	
	while(cin >> n && n) {
		for(i = 0; i < n; i++) {
			cin >> len;
			
			prev = 0;
			for(j = 0; j < len; j++) {
				cin >> curr;
				diff[j] = curr - prev;
				prev = curr;
				
				for(k = j; k >=0; k--)
					if(diff[k] > 0) {
						cout << j - k + 1
							 << " ";
						diff[k]--;
						break;
					}
			}
			
			cout << endl;
			
		}
	}
	
	return 0;
}
