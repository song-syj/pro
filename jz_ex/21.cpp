#include<stack>
#include<iostream>
#include<assert.h>

using namespace std;

template<typename T>
class StackWithMin {
public:
	void push(const T& value);
	T pop();
	T min();
	bool empty();
private:
	stack<T> m_data;
	stack<T> m_min;
};

template<typename T>
void StackWithMin<T>::push(const T& value)
{
	m_data.push(value);
	if(m_min.size() == 0 || m_min.top() > value)
		m_min.push(value);
	else
		m_min.push(m_min.top());
}

template<typename T>
T StackWithMin<T>::pop()
{
	assert(m_min.size() > 0 && m_data.size() > 0);
	T data;
	data = m_data.top();
	m_min.pop();
	m_data.pop();

	return data;
}

template<typename T>
T StackWithMin<T>::min()
{
	assert(m_min.size() > 0 && m_data.size() > 0);

	return m_min.top();
}

template<typename T>
bool StackWithMin<T>::empty()
{
	return m_min.empty() || m_data.empty();
}

int main()
{
	int data[] = {3, 4, 2, 1};
	int length = sizeof(data) / sizeof(int);
	StackWithMin<int> stk;
	for(int i = 0; i < length; i++)
		stk.push(data[i]);
	for(;!stk.empty();) {
		cout << stk.min() << " ";
		cout << stk.pop() << endl;
	}

	return 0;
}
