//ţ���� JZ64 ��1+2+3+...+n
//����ʹ�ó˳�����for,while,if,else,switch,case�ȹؼ��ּ������ж����(A?B:C)
//���Ӳ�����λ���㣬���ܹ�ʽֱ�Ӽ���
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
		//Sum a[n];//C99��֧�ֱ䳣����
		//�ù��캯������n��
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