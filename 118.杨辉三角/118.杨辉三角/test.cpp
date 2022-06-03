#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> ret;
        //���ﲻ����reserve����Ϊreserveֻ�����ݣ������ʼ��������������ռ����ݻ������
        ret.resize(numRows);//�൱������������������vector<int>
        //���ռ�
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