#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
//暴力求解
class Solution {
public:
    vector<int> missingTwo(vector<int>& nums)
    {
        vector<int> ret;
        sort(nums.begin(), nums.end());
        if (nums[0] != 1)
            ret.push_back(1);
        if (nums[0] == 3)
            ret.push_back(2);
        for (int i = 0; i < nums.size(); ++i)
        {
            if (i + 1 < nums.size() && nums[i] + 1 != nums[i + 1])
            {
                //有可能两个数连在一起缺失
                while (nums[i] + 1 != nums[i + 1])
                {
                    nums[i]++;
                    if (ret.size() < 2)
                    {
                        ret.push_back(nums[i]);
                    }
                    else
                    {
                        return ret;
                    }
                }
            }
        }
        if (ret.empty())
        {
            ret.push_back(nums.back() + 1);
            ret.push_back(nums.back() + 2);
        }
        else if (ret.size() == 1)
        {
            ret.push_back(nums.back() + 1);
        }
        return ret;
    }
};
//异或求解
class Solution2 {
public:
    int bit(int num)
    {
        //找到为1的那位
        int count = 0;
        while (num)
        {
            if (num % 2 != 1)
            {
                ++count;
                num /= 2;
            }
            else
            {
                break;
            }
        }
        return count;
    }
    vector<int> missingTwo(vector<int>& nums) {
        int n = nums.size() + 2;//少两个给补上来
        int _xor = 0;
        for (int i = 0; i < nums.size(); ++i)
        {
            _xor ^= nums[i];
        }
        for (int i = 1; i <= n; ++i)
        {
            _xor ^= i;
        }
        //能得到只有两个不存在数的异或和
        //找为1的那位
        int bt = bit(_xor);
        int ret1 = 0, ret2 = 0;
        for (int i = 1; i <= n; ++i)
        {
            if ((i >> bt) % 2 == 1)
            {
                ret1 ^= i;
            }
            else
            {
                ret2 ^= i;
            }
        }
        for (auto e : nums)
        {
            if ((e >> bt) % 2 == 1)
            {
                ret1 ^= e;
            }
            else
            {
                ret2 ^= e;
            }
        }
        return vector<int>{ret1, ret2};
    }
};
int main()
{
    vector<int> nums{ 1 };
    auto it = Solution2().missingTwo(nums);
    for (auto e : it)
    {
        cout << e << endl;
    }
    return 0;
}