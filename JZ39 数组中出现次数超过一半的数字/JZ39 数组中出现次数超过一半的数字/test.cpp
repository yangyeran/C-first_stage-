#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    int MoreThanHalfNum_Solution(vector<int> numbers)
    {
        int x = numbers.size() / 2;
        int count = 1, i = 0;
        sort(numbers.begin(), numbers.end());
        while (i < numbers.size())
        {
            while ((i + 1) < numbers.size() && numbers[i] == numbers[i + 1])
            {
                ++i;
                ++count;
            }
            if (count > x)
            {
                break;
            }
            else {
                count = 1;
                ++i;
            }
        }
        return numbers[i];
    }
};
int main()
{
    Solution().MoreThanHalfNum_Solution(vector<int>() = { 3,3,3,3,3,2,2,2,2 });
}