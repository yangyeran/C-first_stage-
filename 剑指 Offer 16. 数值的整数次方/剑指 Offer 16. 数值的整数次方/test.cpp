#include<iostream>
#include<vector>
using namespace std;
class Solution1 {
public:
    //������
    double myPow(double x, int n) {
        if (n == 0)//���n==0����ʾ�η���1������
            return 1;
        else if (n == 1)//n==1�������ֱ�ӷ���x
            return x;
        else if (n < 0)//����ת��Ϊ����(���ֱ��д-n�������->1.00000,-214783648��������0--214783647)
            return (1 / x) * myPow(1 / x, -(n + 1));
        if (n % 2 == 0)
        {
            return myPow(x * x, n / 2);
        }
        else
        {
            //����
            return x * myPow(x * x, n / 2);
        }

    }
};
class Solution2
{
public:
    double myPow(double x, int n)
    {
        //ѭ��ʵ�ֿ�����
        double ret = 1;
        if (n < 0)
        {
            x = 1 / x;
            ret *= x;
            n = -(n + 1);
        }
        while (n)
        {
            //���n==1��ʱ�򷵻�x������0��ʱ���ó�
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