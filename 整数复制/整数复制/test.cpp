//题目描述
//给定一个整数n(n > 0)，将其重复m(m >= 1)次并将这些数前后拼接，我们可以得到一个长度为原有数m倍长度的更大整数
//例如n = 123，m = 3，则拼接结果为123123123，对该数输出其除以k之后的余数。
//仅一行，包含三个整数n、m和k。(1 < n, m, k < 1000)
#include<iostream>
#include<vector>
#include<string>
using namespace std;
void NumSwitch(int n, int m,int k, string& str,vector<string>& vs)
{
    string tmp = to_string(n);
    for(size_t i=0;i<m;++i)
    {
        vs[i] += tmp;
    }
}
int Remainder(vector<string>& vs, int k)
{
    size_t len = vs.size();
    int count = 0;
    for (size_t i = 0; i < len; ++i)
    {
        size_t num = stoll(vs[i]);
        num %= k;
        count = num;
        if (num != 0 && i+1<len)
        {
            string str = to_string(num);
            vs[i + 1].insert(0, str);
        }
    }
    return count;
}
int main()
{
    int n, m, k;
    string str;
    cin >> n >> m >> k;
    vector<string> vs(m);
    NumSwitch(n, m,k, str,vs);
    cout<<Remainder(vs, k)<<endl;
    return 0;
}