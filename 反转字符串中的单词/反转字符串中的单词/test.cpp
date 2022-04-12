#include<iostream>
#include<string>
using namespace std;
class Solution {
public:
    string reverseWords(string s) {
        int i = 0;
        while (i < s.size())
        {
            int begin = i;
            while (i < s.size() && s[i] != ' ')
            {
                i++;
            }
            //到这就是为空
            int end = i-1;
            while (begin < end)
            {
                swap(s[begin], s[end]);
                ++begin;
                --end;
            }
            i += 1;
        }
        return s;
    }
};
int main()
{
    string st="Let's take LeetCode contest";
    Solution st1;
    cout << st1.reverseWords(st) << endl;
    return 0;
}