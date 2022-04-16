#include<iostream>
#include<string>
using namespace std;
class Solution {
public:
    int StrToInt(string str) {
        int num = 0, flag = 1;
        if (str[0] == '-')
        {
            flag = -1;
        }
        for (int i = 0; i < str.size(); i++)
        {
            if (str[i] == '-' || str[i] == '+')
                continue;
            if (str[i] >= '0' && str[i] <= '9')
                num = num * 10 + (str[i] - '0');
            else
                return 0;
        }
        return num * flag;
    }
};