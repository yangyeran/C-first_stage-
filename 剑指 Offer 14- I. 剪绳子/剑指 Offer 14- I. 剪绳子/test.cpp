#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int cuttingRope(int n) {
        //动态规划
        /*if(n<=3)
            return n-1;
        vector<int> dp(n+1);
        dp[1]=1;
        dp[2]=2;
        dp[3]=3;
        for(int i=4;i<=n;++i)
        {
            for(int j=1;j<=i/2;++j)
            {
                dp[i]=max(dp[i],max(dp[j],dp[i-j]*j));
            }
        }
        return dp[n];*/
        //数学算法就是3越多的话结果就会越大
        if (n <= 3)
            return n - 1;
        int ret = 1;
        while (n >= 3)
        {
            if (n - 3 == 1)
            {
                ret *= 2;
                n -= 2;
                continue;
            }
            ret *= 3;
            n -= 3;
        }
        return ret * (n == 0 ? 1 : n);
    }
};
int main()
{
    cout << Solution().cuttingRope(6) << endl;
}