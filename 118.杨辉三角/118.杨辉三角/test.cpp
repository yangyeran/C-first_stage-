#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> ret;
        //这里不能用reserve，因为reserve只是扩容，不会初始化，后续给里面空间扩容会出问题
        ret.resize(numRows);//相当于数组里面存的类型是vector<int>
        //开空间
        for (size_t i = 0; i < numRows; ++i)
        {
            ret[i].resize(i+1, 0);
            ret[i][0] = 1;
            ret[i][i] = 1;
        }
        for (size_t i = 0; i < numRows; ++i)
        {
            for (size_t j = 0; j <= i; ++j)
            {
                if (ret[i][j] == 0)
                {
                    ret[i][j] = ret[i - 1][j] + ret[i - 1][j - 1];
                }
            }
        }
        return ret;
    }
};
int main()
{
    Solution().generate(5);
}