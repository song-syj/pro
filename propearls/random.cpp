#include"random.h"
#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<set>

using namespace std;

int randint(int l, int u)
{
	return l + rand()%(l-u+1);
}

void genknuth(int m, int n)
{
	int select =m;
	int remain = n;
	srand(time(NULL));
	
	for(int i = 0; i < n; i++)
		if(rand() % remain < select) {
			cout << i << endl;
			select--;
			remain--;
		}
}

void gensets(int m, int n)
{
	set<int> S;
	
	while (S.size() < m)
		S.insert(rand() % n);
	set<int>::iterator i;
	for(i = S.begin(); i != S.end(); i++)
		cout << *i << endl;
}

void genshuf(int m, int n)
{
	int i, j, tmp;
	int *x = new int[n];

	for(i = 0; i < n; i++) {
		x[i] = i;
	}

	srand(time(NULL));
	for(i = 0; i < m; i++) {
		j = randint(i, n-1);
		tmp = x[i];
		x[i] = x[j];
		x[j] = tmp;
	}

	sort(x, x+m);

	for(i = 0; i < m; i++) {
		cout << x[i] << endl;
	}
}

void genfloyd(int m, int n)
{
	set<int> S;
	set<int>::iterator i;

	srand(time(NULL));
	for(int j = n-m; j < n; j++) {
		int t = rand() % (j+1);
		if(S.find(t) == S.end())
			S.insert(t);
		else
			S.insert(j);
	}

	for(i = S.begin(); i != S.end(); i++) {
		cout << *i << endl;
	}
}



















