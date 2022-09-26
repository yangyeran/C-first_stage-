#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include <functional>
using namespace std;
//暴力求解
//const static vector<int> num{ 0,0,1,-1,-1,1,1,-1,0,1 };
////代表是否出现了相应的数
////2,5,6,9为映射至少需要出现一次
////0 , 1 , 8 可有可无
////3,4, 7  不能出现
//    int rotatedDigits(int n) {
//        int ret = 0;
//        for (int i = 1; i <= n; ++i)
//        {
//            bool need = true, diff = false;
//            string st = to_string(i);
//            for (auto e : st)
//            {
//                if (num[e - '0'] == 1)
//                    diff = true;
//                else if (num[e - '0'] == -1)
//                    need = false;
//            }
//            if (need && diff)
//            {
//                ++ret;
//            }
//        }
//        return ret;
//    }
//

//数位DP
class Solution1 {
public:
    int rotatedDigits(int n) {
        vector<int> digits;
        while (n) {
            digits.push_back(n % 10);
            n /= 10;
        }
        reverse(digits.begin(), digits.end());

        memset(memo, -1, sizeof(memo));
        function<int(int, bool, bool)> dfs = [&](int pos, bool bound, bool diff) -> int {
            if (pos == digits.size()) {
                return diff;
            }
            if (memo[pos][bound][diff] != -1) {
                return memo[pos][bound][diff];
            }

            int ret = 0;
            for (int i = 0; i <= (bound ? digits[pos] : 9); ++i) {
                if (check[i] != -1) {
                    ret += dfs(
                        pos + 1,
                        bound && (i == digits[pos]),
                        diff || (check[i] == 1)
                    );
                }
            }
            return memo[pos][bound][diff] = ret;
        };

        int ans = dfs(0, true, false);
        return ans;
    }

private:
    static constexpr int check[10] = { 0, 0, 1, -1, -1, 1, 1, -1, 0, 1 };
    int memo[5][2][2];
};
class Solution {
public:
    int bfs(int pos, bool bound, bool diff,vector<int> nums)
    {
        if (pos == nums.size()) // 如果最后一个位置等于它的size，并且如果为真就代表又找到一个符合的数，如果为假就不是符合的数
            return diff;
        //如果某个位置的值不为-1说明已经查找过一次了，就没有必要再进行查找了，直接返回存的值就好
        if (memo[pos][bound][diff] != -1)
            return memo[pos][bound][diff];
        int ret = 0;
        //遍历如果是贴着的那么就小于等于nums[pos] 如果不是贴着的那么就是0--9都可以
        for(int i = 0;i <= (bound ? nums[pos] : 9);++i)
        {
            //只有符合条件的才能够继续递归
            if (check[i] != -1)
            {
                ret += bfs(pos + 1, bound && (i == nums[pos]), diff || (check[i]==1), nums);
            }
        }
        return memo[pos][bound][diff] = ret;
    }
    int rotatedDigits(int n) {
        vector<int> nums;
        //首先先把n给存进一个vector，方便去使用位数
        while (n)
        {
            nums.push_back(n % 10);
            n /= 10;
        }
        reverse(nums.begin(), nums.end());
        memset(memo, -1, sizeof(memo));
        int i = 0;
        //实现一个子函数，传入的是当前位置，和是否贴边放(如果前面都是贴边放的，那么pos位置需要受到限制，反之则不需要)，是否含有可旋转的数
        int ret = bfs(0, true, false,nums);
        return ret;
    }
private:
    //检查是否含有无法旋转的数
    static int check[10];
    //第一个表示的是位数，第二和第三表示true or false 
    int memo[5][2][2];
};
int Solution::check[10] = { 0, 0, 1, -1, -1, 1, 1, -1, 0, 1 };
class Solution2 {
public:
    int bfs(int pos, bool bound, bool diff, vector<int> nums)
    {
        if (pos == nums.size())
            return diff; //举个例子如果是n=10，第一位是0 -> bound=false,1->diff=false->2->diff->true代表这个是可旋转数记录一下
        if (memo[pos][bound][diff] != -1) //代表找过相同的
            return memo[pos][bound][diff];
        int ret = 0;//用来计数的
        for (int i = 0; i <= (bound ? nums[pos] : 9); ++i)
        {
            if (check[i] != -1)//可有可无的只是减少了几次判断
            {
                ret += bfs(pos + 1, bound && (i == nums[pos]), diff || check[i] == 1, nums);
            }
        }
        return memo[pos][bound][diff] = ret;
    }
    int rotatedDigits(int n) {
        vector<int> nums;
        //首先先把n给存进一个vector，方便去使用位数
        while (n)
        {
            nums.push_back(n % 10);
            n /= 10;
        }
        reverse(nums.begin(), nums.end());
        memset(memo, -1, sizeof(memo));
        int i = 0;
        int ret = bfs(0, true, false, nums);
        return ret;
    }
private:
    //检查是否含有无法旋转的数
    static int check[10];
    //第一个表示的是位数，第二和第三表示true or false 
    int memo[5][2][2];
};
int Solution2::check[10] = { 0, 0, 1, -1, -1, 1, 1, -1, 0, 1 };
int main()
{
    cout << Solution1().rotatedDigits(10) << endl;
    cout << Solution().rotatedDigits(10) << endl;
    cout << Solution2().rotatedDigits(10) << endl;
    return 0;
}