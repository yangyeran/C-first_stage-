#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class A 
{
public:
	virtual void fun(int i = 2)
	{
		cout << "funA->"<< i << endl;
	}
};
class B :public A
{
public:
	virtual void fun(int i = 1)
	{
		cout << "funB->" << i << endl;
	}
};
//int main()
//{
//	A* p = new B();
//	p->fun();
//}


//������������������1�ĸ���(��������)
#include<iostream>
using namespace std;
int GetOnenums(int n)
{
    int count = 0;
    while (n)
    {
        if (n % 2 == 1)
            count++;
        n /= 2;
    }
    return count;
}
//int main()
//{
//    int n;
//    while (cin >> n)
//    {
//        cout << GetOnenums(n) << endl;
//    }
//    return 0;
//}
//ţ��������
int findMinimum(int n, vector<int> left, vector<int> right) {
    // write code here
    //�������=Ϊ0��������+ʣ�µ���С������-��С���Ǹ���+1(����-��С����ɫ��+1)
    int l_min = 26;//������ܸ�ֵ��һ��Ԫ�ص�ֵ����Ϊ��һ��Ԫ�������0����ô�����Ͳ��ᱻ�ı�
    int r_min = 26;//�����СֵҪ����Ƿ�0����Сֵ��Ϊ������಻����26������ֱ�Ӹ�ֵ26��
    int l_sum = 0, r_sum = 0;
    int ret = 0;
    for (int i = 0; i < n; ++i)
    {
        if (left[i] * right[i] == 0)
        {
            //������Ϊ0������
            ret += left[i] + right[i];
        }
        else
        {
            l_sum += left[i];
            r_sum += right[i];
            l_min = min(l_min, left[i]);
            r_min = min(r_min, right[i]);
        }
    }
    return ret + min(l_sum - l_min + 1, r_sum - r_min + 1) + 1;
}
int main()
{
    findMinimum(4, vector<int>{4,5,3,2}, vector<int>{0,1,2,3});
}