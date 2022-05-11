#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    vector<string> arr = { "","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz" };
    void _letterCombinations(vector<string>& ret, const string& digits, int len, string combin)
    {
        if (len == digits.size())
        {
            ret.push_back(combin);
            return;
        }
        string str = arr[digits[len]-'0'];
        for (size_t i = 0; i < str.size(); ++i)
        {
            _letterCombinations(ret, digits, len + 1, combin + str[i]);
        }
    }
    vector<string> letterCombinations(string digits) {
        vector<string> ret;
        string combin;
        if (digits.empty())
            return ret;
        //ªÿÀ›À„∑®
        _letterCombinations(ret, digits, 0, combin);
        return ret;
    }
};
int main()
{
    Solution().letterCombinations("23");
}