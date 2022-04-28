#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {

        for (int i = 0; i < nums.size() - 1; ++i)
        {
            if (nums[i] == nums[i + 1])
            {
                size_t sz = nums.size();
                nums.erase(nums.begin() + i, nums.end() - (sz - i - 1));
                while((i + 1 < nums.size()) && nums[i] == nums[i + 1])
                {
                    size_t sz = nums.size();
                    nums.erase(nums.begin() + i, nums.end() - (sz - i - 1));
                }
            }
        }
        return nums.size();
    }
};
int main()
{
    vector<int>nums = {0,0,0,0,3};
    Solution().removeDuplicates(nums);
    return 0;
}