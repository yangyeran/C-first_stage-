#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int temp = nums[0];
        vector<int> ret;
        //两个相同的数按位与就会为0，这样可以找到两个只出现一次的数的异或的结果
        //因为同为0异为1，可以找到区分点，可以就是将异或第一个1为标准
        //通过异或结果可以把数组分为两类，让两组数再次分开异或
        for (size_t i = 1; i < nums.size(); ++i)
        {
            temp ^= nums[i];
        }
        int num1 = 0, num2 = 0;
        int count = 1;
        //找temp第几位是1，同时为了方便后续分组，定义一个count为标志位，来划分两组数
        while ((temp & 1) == 0)
        {
            temp >>= 1;
            count <<= 1;
        }
        for (size_t i = 0; i < nums.size(); ++i)
        {
            //与count异或为0和不为0两种情况
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