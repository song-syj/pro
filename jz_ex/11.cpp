#include<iostream>
using namespace std;

bool g_InvalidInput = false;

bool equal(double x, double y)
{
	if((x - y > -1e-10) && (x - y < 1e-10))
		return true;
	else 
		return false;
}

double PowerWithUnsignedExponent(double base, unsigned int exponent)
{
	double result = 1.0;
	while(exponent) {
		if(exponent & 0x1)
			result *= base;
		base *= base;
		exponent >>= 1;
	}

	return result;
}

double Power(double base, int exponent)
{
	g_InvalidInput = false;

	if((equal(base, 0.0) && exponent < 0)) {
		g_InvalidInput = true;
		return 0.0;
	}

	unsigned int absExponent = exponent;
	if(exponent < 0)
		absExponent = -exponent;

	double result = PowerWithUnsignedExponent(base, absExponent);
	if(exponent < 0) {
		result = 1.0 / result;
	}
	
	return result;
}

int main()
{
	double result = Power(0.0, -111);
	if(g_InvalidInput)
		cerr << "InvalidInput" << endl;
	else
		cout << result << endl;
	return 0;
}
