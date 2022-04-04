//牛客网 JZ64 求1+2+3+...+n
//不能使用乘除法，for,while,if,else,switch,case等关键字及条件判断语句(A?B:C)
//附加不能用位运算，不能公式直接计算
#include<iostream>
using namespace std;
class Sum
{
public:
	Sum()
	{
		_ret += _num;
		++_num;
	}
	static void Init()
	{
		_num = 1;
		_ret = 0;
	}
	static int Getret()
	{
		return _ret;
	}
private:
	static int _num;
	static int _ret;
};
int Sum::_ret = 0;
int Sum::_num = 1;
class Solution
{
public:
	int sum_Solution(int n)
	{
		//Sum a[n];//C99才支持变常数组
		//让构造函数调用n次
		Sum::Init();
		Sum* p = new Sum[n];
		delete[]p;
		return Sum::Getret();
	}
};
int main()
{
	int n = 0;
	cin >> n;
	Solution a;
	cout << a.sum_Solution(n)<< endl;
	cout << Solution().sum_Solution(n) << endl;
	return 0;
}