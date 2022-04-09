#include<iostream>
using namespace std;
class Stack
{
public:
	Stack(int capacate = 4)
		:_capacate(capacate)
	{
		int* p = new int[_capacate];
		_top = 0;
	}
	~Stack()
	{
		delete[] p;
		_top = _capacate = 0;
	}
private:
	int _capacate;
	int _top;
	int* p;
};
int main()
{
	Stack* st = new Stack;
	Stack* st1 = (Stack*)operator new(sizeof(Stack));
	delete st;
	operator delete(st1);
	return 0;
}