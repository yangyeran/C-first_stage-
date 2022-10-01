#include<iostream>
#include<vector>
using namespace std;
class Solution1 {
public:
    //快速幂
    double myPow(double x, int n) {
        if (n == 0)//如果n==0，表示次方乘1就行了
            return 1;
        else if (n == 1)//n==1，算好了直接返回x
            return x;
        else if (n < 0)//将幂转化为正数(如果直接写-n，会溢出->1.00000,-214783648正整数是0--214783647)
            return (1 / x) * myPow(1 / x, -(n + 1));
        if (n % 2 == 0)
        {
            return myPow(x * x, n / 2);
        }
        else
        {
            //奇数
            return x * myPow(x * x, n / 2);
        }

    }
};
class Solution2
{
public:
    double myPow(double x, int n)
    {
        //循环实现快速幂
        double ret = 1;
        if (n < 0)
        {
            x = 1 / x;
            ret *= x;
            n = -(n + 1);
        }
        while (n)
        {
            //如果n==1的时候返回x，等于0的时候不用乘
            if (n % 2 == 1)
                ret = ret * x;
            x = x * x;
            n /= 2;
        }
        return ret;
    }
};
int main()
{
    //cout << Solution1().myPow(1.00000, -214783648) << endl;
    cout << Solution1().myPow(2.00000,10) << endl;
    cout << Solution2().myPow(2.00000,-2) << endl;
}