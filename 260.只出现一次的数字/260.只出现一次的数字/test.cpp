#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int temp = nums[0];
        vector<int> ret;
        //������ͬ������λ��ͻ�Ϊ0�����������ҵ�����ֻ����һ�ε��������Ľ��
        //��ΪͬΪ0��Ϊ1�������ҵ����ֵ㣬���Ծ��ǽ�����һ��1Ϊ��׼
        //ͨ����������԰������Ϊ���࣬���������ٴηֿ����
        for (size_t i = 1; i < nums.size(); ++i)
        {
            temp ^= nums[i];
        }
        int num1 = 0, num2 = 0;
        int count = 1;
        //��temp�ڼ�λ��1��ͬʱΪ�˷���������飬����һ��countΪ��־λ��������������
        while ((temp & 1) == 0)
        {
            temp >>= 1;
            count <<= 1;
        }
        for (size_t i = 0; i < nums.size(); ++i)
        {
            //��count���Ϊ0�Ͳ�Ϊ0�������
            if ((nums[i] & count) == 0)
                num1 ^= nums[i];
            else
                num2 ^= nums[i];
        }
        ret.push_back(num1);
        ret.push_back(num2);
        return ret;
    }
};
int main()
{
    vector<int> nums = { 1,3,2,5,2,1 };
    Solution().singleNumber(nums);
}