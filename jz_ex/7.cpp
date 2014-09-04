#include<stack>
#include<queue>
#include<iostream>

using namespace std;

template <typename T> class CQueue
{
public:
	//CQueue(void);
	//~CQueue(void);

	void appendTail(const T& node);
	T deleteHead();
	bool empty() { return stack1.empty()&&stack2.empty();}
private:
	stack<T> stack1;
	stack<T> stack2;
};

template <typename T> 
void CQueue<T>::appendTail(const T& node)
{
	stack1.push(node);
}

template <typename T> 
T CQueue<T>::deleteHead()
{
	if(stack2.empty()) {
		while(!stack1.empty()) {
			T data = stack1.top();
			stack2.push(data);
			stack1.pop();
		}
	}

	if(stack2.empty()) {
		cerr << "queue is empty" << endl;
		exit(1);
	}
		//throw logic_error("queue is empty");

	T head = stack2.top();
	stack2.pop();

	return head;
}

template<typename T>
class CStack {
public:
	void appendTail(const T& node);
	T deleteTail();
	bool empty();
private:
	queue<T> queue1;
	queue<T> queue2;
};

template<typename T>
void CStack<T>::appendTail(const T& data)
{
	if(!queue1.empty())
		queue1.push(data);
	else
		queue2.push(data);
}

template<typename T>
T CStack<T>::deleteTail()
{
	queue<T> *pFirst;
	queue<T> *pSecond;
	if(queue1.empty() && queue2.empty()) {
		cerr << "stack is empty" << endl;
		exit(1);
	}

	if(!queue1.empty()) {
		pFirst = &queue1;
		pSecond = &queue2;
	} else {
		pFirst = &queue2;
		pSecond = &queue1;
	}

	while(pFirst->size() > 1) {
		T data = pFirst->front();
		pSecond->push(data);
		pFirst->pop();
	}

	T tail = pFirst->front();
	pFirst->pop();

	return tail;
}

template<typename T>
bool CStack<T>::empty()
{
	return queue1.empty() && queue2.empty();
}

int main()
{
	CStack<int> stk;
	int data[] = {2, 4, 5, 9 ,11};
	int size = sizeof(data)/ sizeof(int);
	for(int i = 0; i < size; i++)
		stk.appendTail(data[i]);
	while(!stk.empty()) {
		int data = stk.deleteTail();
		cout << data << " ";
	}	

	cout << endl;

	return 0;
}
