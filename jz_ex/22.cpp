#include<stack>
#include<iostream>

using namespace std;

bool IsPopOrder(const int*pPush, const int* pPop, int length)
{
	if(length <= 0 || pPush == NULL || pPop == NULL)
		return false;

	stack<int> stk;
	int indexPush = 0;
	int indexPop = 0;

	while(indexPush < length) {
		if(stk.empty() || stk.top() != pPop[indexPop]){
			stk.push(pPush[indexPush++]);
		} 

		while(!stk.empty() && stk.top() == pPop[indexPop]) {
			stk.pop();
			indexPop++;
		}
	}

	if(stk.empty()) 
		return true;
	else 
		return false;
}

int main()
{
	int pushSeq[] = {1, 2, 3, 4, 5};
	int popSeq[] = {5, 4, 3, 2, 1};
	//int popSeq[] = {4, 5, 3, 2, 1};
	//int popSeq[] = {4, 3, 5, 1, 2};

	cout << boolalpha << IsPopOrder(pushSeq, popSeq, 5) << endl;

	return 0;
}
