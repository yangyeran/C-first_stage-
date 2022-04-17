#include<iostream>
#include<string>
using namespace std;
class Solution {
public:
    bool isPalindrome(string s) {
        size_t begin = 0;
        string str;
        while (begin < s.size())
        {
            if (s[begin] >= 65 && s[begin] <= 90)
            {
                s[begin] += 32;
            }
            if ((s[begin] >= 97 && s[begin] <= 122) || (s[begin] >= 48) && s[begin] <= 57)
                str += s[begin];
            ++begin;
        }
        begin = 0;
        if (str.size() == 0)
            return true;
        size_t end = str.size() - 1;
        while (begin < end)
        {
            if (str[begin] == str[end])
            {
                ++begin;
                --end;
            }
            else
                return false;
        }
        return true;
    }
};