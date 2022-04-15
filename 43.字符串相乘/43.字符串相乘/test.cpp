#include<iostream>
#include<string>
using namespace std;
class Solution {
public:
    string Ridenum(string const& num1, int n, int count)
    {
        string retstr;
        int n1 = num1.size() - 1;
        int next = 0;
        while (n1 >= 0)
        {
            while (count > 0)
            {
                retstr += '0';
                --count;
            }
            int num = (num1[n1] - '0') * n + next;
            if (num > 9)
            {
                next = num / 10;
                num %= 10;
            }
            else
                next = 0;
            retstr += (num + '0');
            --n1;
        }
        if (next > 0)
            retstr += (next + '0');
        reverse(retstr.begin(), retstr.end());
        return retstr;
    }
    string Addstring(string const& str1, string const& str2)
    {
        int end1 = str1.size() - 1;
        int end2 = str2.size() - 1;
        int next = 0;
        int retval = 0;
        string Retstr;
        //让长的结束在结束，控制比较简单
        while (end1 >= 0 || end2 >= 0)
        {
            int s1 = 0;
            if (end1 >= 0)
                s1 = str1[end1] - '0';
            int s2 = 0;
            if (end2 >= 0)
                s2 = str2[end2] - '0';
            retval = s1 + s2 + next;
            if (retval > 9)
            {
                next = 1;
                retval -= 10;
            }
            else
                next = 0;//不控制next会导致误加
            Retstr += (retval + '0');
            --end2;
            --end1;
        }
        if (next == 1)
            Retstr += '1';
        reverse(Retstr.begin(), Retstr.end());
        return Retstr;
    }
    string multiply(string num1, string num2) {
        //需要进位
        int next = 0;
        int n1 = num1.size() - 1;
        int n2 = num2.size() - 1;
        //规定num1>=num2,这样就是用num2中的每一个字符去乘num1
        if (num1[0] == '0' || num2[0] == '0')
        {
            return "0";
        }
        if (n1 < n2)
        {
            swap(n1, n2);
            swap(num1, num2);
        }
        //以短的为结尾
        int ncopy2 = n2;
        string* StrArr = new string[n2 + 1];
        string str, retstr;
        while (ncopy2 >= 0)
        {
            str = Ridenum(num1, (num2[ncopy2] - '0'), n2 - ncopy2);
            StrArr[ncopy2] = str;
            --ncopy2;
        }
        while (n2 >= 0)
        {
            retstr = Addstring(StrArr[n2], retstr);
            --n2;
        }
        return retstr;
    }
};
int main()
{
    Solution().multiply("9", "9");
    return 0;
}