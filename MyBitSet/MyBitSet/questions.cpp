#include<iostream>
#include<bitset>
using namespace std;
#include "MyBitSet.h"
/*1.����100�ڸ�����������㷨�ҵ�ֻ����һ�ε�������
2. �������ļ����ֱ���100�ڸ�����������ֻ��1G�ڴ棬����ҵ������ļ�������
3. λͼӦ�ñ��Σ�1���ļ���100�ڸ�int��1G�ڴ棬����㷨�ҵ����ִ���������2�ε���������*/

//1.��һ����˼·������������λͼ��ͳ��00��ʾû�� 01��ʾ������һ�Σ�11��ʾ���μ�����
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
		//11��ʾ���μ����ϣ����ô���
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

//2. �������ļ����ֱ���100�ڸ�����������ֻ��1G�ڴ棬����ҵ������ļ�������
//���������ļ��ֱ��������λͼ��set1��set2��a.��set1�ж�ȡ���ݿ���set2����û�У��о��ǽ���
//                                          b.��set1��set2��Ӧλ����(&)һ�£������ʣ1��λ�þ��ǽ���


//3.λͼӦ�ñ��Σ�1���ļ���100�ڸ�int��1G�ڴ棬����㷨�ҵ����ִ���������2�ε���������
template<size_t N>
class TwoOrOneNum
{
public:
	void set(const size_t& k)
	{
		if (_bs1.test(k) == 0 && _bs2.test(k) == 0) //00-->01 0�α�һ��
		{
			_bs2.set(k);
		}
		else if (_bs1.test(k) == 0 && _bs2.test(k) == 1)  //01-->10 һ�α�����
		{
			_bs1.set(k);
			_bs2.reset(k);
		}
		else if (_bs1.test(k) == 1 && _bs2.test(k) == 0) //10-->11 ��������
		{
			_bs2.set(k);
		}
		//11��ʾ�������ϣ����ô���
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