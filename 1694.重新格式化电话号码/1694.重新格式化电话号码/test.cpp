#include<iostream>
#include<vector>
#include<string>
using namespace std;
class Solution {
public:
    string reformatNumber(string number) {
        vector<string> str;
        string temp;
        for (size_t i = 0; i < number.size(); ++i)
        {
            if (number[i] != ' ' && number[i] != '-')
            {
                temp += number[i];
            }
            if (temp.size() == 3)
            {
                str.push_back(temp);
                temp.clear();
            }
        }
        string ret;
        //遍历完一遍了,而且如果temp的size==1则表示剩了4个数
        //size==2 表示剩了两个数
        for (size_t i = 0; i < str.size(); ++i)
        {
            if (i < str.size() - 1)
                ret = ret + str[i] + '-';
            else
                ret += str[i];
        }
        if (!temp.empty())
        {
            if (ret == "")
            {
                ret += temp;
                return ret;
            }
            if (temp.size() == 1)
            {
                ret.insert(ret.size() - 1, "-");
                ret += temp;
            }
            else //size==2
            {
                ret = ret + '-' + temp;
            }
        }
        return ret;
    }
};
int main()
{
    Solution().reformatNumber("1 - 23 - 45 6");
}