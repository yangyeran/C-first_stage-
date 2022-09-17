#include<iostream>
#include<bitset>
using namespace std;
#include "MyBitSet.h"
/*1.给定100亿个整数，设计算法找到只出现一次的整数？
2. 给两个文件，分别有100亿个整数，我们只有1G内存，如何找到两个文件交集？
3. 位图应用变形：1个文件有100亿个int，1G内存，设计算法找到出现次数不超过2次的所有整数*/

//1.第一个的思路就是来用两个位图来统计00表示没有 01表示出现了一次，11表示两次及以上
template<size_t N>
class OnlyOneNum
{
public:
	void set(const size_t& k)
	{
		if (_bs1.test(k) == 0 && _bs2.test(k) == 0)
		{
			_bs2.set(k);
		}
		else if (_bs1.test(k) == 0 && _bs2.test(k) == 1)
		{
			_bs1.set(k);
		}
		//11表示两次及以上，不用处理
	}
	void PrintOneNum()
	{
		for (size_t i = 0; i < N; ++i)
		{
			if (_bs1.test(i) == 0 && _bs2.test(i) == 1)
			{
				cout << i << endl;
			}
		}
	}
private:
	bitset<N> _bs1;
	bitset<N> _bs2;
};

//2. 给两个文件，分别有100亿个整数，我们只有1G内存，如何找到两个文件交集？
//就是两个文件分别存在两个位图中set1和set2，a.从set1中读取数据看看set2中有没有，有就是交集
//                                          b.将set1和set2对应位置与(&)一下，如果还剩1的位置就是交集


//3.位图应用变形：1个文件有100亿个int，1G内存，设计算法找到出现次数不超过2次的所有整数
template<size_t N>
class TwoOrOneNum
{
public:
	void set(const size_t& k)
	{
		if (_bs1.test(k) == 0 && _bs2.test(k) == 0) //00-->01 0次变一次
		{
			_bs2.set(k);
		}
		else if (_bs1.test(k) == 0 && _bs2.test(k) == 1)  //01-->10 一次变两次
		{
			_bs1.set(k);
			_bs2.reset(k);
		}
		else if (_bs1.test(k) == 1 && _bs2.test(k) == 0) //10-->11 两次以上
		{
			_bs2.set(k);
		}
		//11表示两次以上，不用处理
	}
	void PrintTwoNum()
	{
		for (size_t i = 0; i < N; ++i)
		{
			if (_bs1.test(i) == 0 && _bs2.test(i) == 1)
			{
				cout << i << endl;
			}
			else if (_bs1.test(i) == 1 && _bs2.test(i) == 0)
			{
				cout << i << endl;
			}
		}
	}
private:
	bitset<N> _bs1;
	bitset<N> _bs2;
};

void test1()
{
	TwoOrOneNum<100> tn;
	int a[] = { 99,0,4,50,33,44,2,5,99,0,50,99,50,2 };
	for (auto e : a)
	{
		tn.set(e);
	}
	tn.PrintTwoNum();
}
int main()
{
	test1();
}