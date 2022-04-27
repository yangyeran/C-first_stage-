#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int a = 0, b = 0;
        for (auto i : nums)
        {
            b = (b ^ i) & (~a);
            a = (a ^ i) & (~b);
        }
        return b;
    }
};
int main()
{
    vector<int>nums{ 2,2,3,2 };
    cout << Solution().singleNumber(nums)<<endl;
    return 0;
}