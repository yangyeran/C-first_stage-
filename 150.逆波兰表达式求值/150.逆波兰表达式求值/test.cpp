#include<iostream>
#include<vector>
#include<string>
#include<stack>
using namespace std;
class Solution {
public:
    int evalRPN(vector<string>& tokens)
    {
        stack<int> ret;
        size_t sz = 0;
        while (sz < tokens.size())
        {
            string str = tokens[sz];
            //存储数字部分
            while (sz < tokens.size() && !(str == "+" || str == "-" || str == "*" || str == "/"))
            {
                ret.push(atoi(str.c_str()));
                ++sz;
                str = tokens[sz];
            }
            //处理非数字部分
            while (sz < tokens.size() && (str == "+" || str == "-" || str == "*" || str == "/"))
            {
                int x, y, sum = 0;
                x = ret.top();
                ret.pop();
                y = ret.top();
                ret.pop();
                if (str == "+")
                {
                    sum = y + x;
                    ret.push(sum);
                }
                else if (str == "-")
                {
                    sum = y - x;
                    ret.push(sum);
                }
                else if (str == "*")
                {
                    sum = y * x;
                    ret.push(sum);
                }
                else if (str == "/")
                {
                    sum = y / x;
                    ret.push(sum);
                }
                ++sz;
                if (sz < tokens.size())
                    str = tokens[sz];
            }
        }
        return ret.top();
    }
};
int main()
{
    vector<string> st = { "2","1","+","3","*" };
    Solution().evalRPN(st);
}