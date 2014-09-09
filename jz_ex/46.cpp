#include<iostream>
using namespace std;

typedef unsigned int (*fun) (unsigned int);

unsigned int Teminator(unsigned int n)
{
	return 0;
}

unsigned int Sum(unsigned int n)
{
	static fun fun2[2] = {Teminator, Sum};
	return n + fun2[!!n](n-1);
}

template <unsigned int n> struct Sum_Solution4 {
	enum Value {N = Sum_Solution4<n-1>::N + n};
};

template <> struct Sum_Solution4<1> {
	enum Value {N = 1};
};

int main()
{
	cout << Sum_Solution4<10>::N <<endl;

	return 0;
}
