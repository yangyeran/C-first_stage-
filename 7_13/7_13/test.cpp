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


//查找输入整数二进制1的个数(多组输入)
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
//牛客网手套
int findMinimum(int n, vector<int> left, vector<int> right) {
    // write code here
    //最少情况=为0的手套数+剩下的最小的总数-最小的那个数+1(总数-最小的颜色数+1)
    int l_min = 26;//这个不能赋值第一个元素的值，因为第一个元素如果是0，那么后续就不会被改变
    int r_min = 26;//这个最小值要求的是非0的最小值因为手套最多不超过26，所以直接赋值26了
    int l_sum = 0, r_sum = 0;
    int ret = 0;
    for (int i = 0; i < n; ++i)
    {
        if (left[i] * right[i] == 0)
        {
            //其中有为0的手套
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