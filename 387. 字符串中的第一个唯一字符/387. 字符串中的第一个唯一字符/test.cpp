#include<iostream>
#include<string>
using namespace std;
class Solution {
public:
    int firstUniqChar(string s) {
        int* NumArr = new int[26]{ 0 };
        for (size_t i = 0; i < s.size(); i++)
        {
            NumArr[s[i] - 97]++;
        }
        for (size_t i = 0; i < s.size(); i++)
        {
            if (NumArr[s[i] - 97] == 1)
            {
                return i;
            }
        }
        return -1;
    }
};