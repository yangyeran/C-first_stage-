#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include <functional>
using namespace std;
//�������
//const static vector<int> num{ 0,0,1,-1,-1,1,1,-1,0,1 };
////�����Ƿ��������Ӧ����
////2,5,6,9Ϊӳ��������Ҫ����һ��
////0 , 1 , 8 ���п���
////3,4, 7  ���ܳ���
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

//��λDP
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
        if (pos == nums.size()) // ������һ��λ�õ�������size���������Ϊ��ʹ������ҵ�һ�����ϵ��������Ϊ�پͲ��Ƿ��ϵ���
            return diff;
        //���ĳ��λ�õ�ֵ��Ϊ-1˵���Ѿ����ҹ�һ���ˣ���û�б�Ҫ�ٽ��в����ˣ�ֱ�ӷ��ش��ֵ�ͺ�
        if (memo[pos][bound][diff] != -1)
            return memo[pos][bound][diff];
        int ret = 0;
        //������������ŵ���ô��С�ڵ���nums[pos] ����������ŵ���ô����0--9������
        for(int i = 0;i <= (bound ? nums[pos] : 9);++i)
        {
            //ֻ�з��������Ĳ��ܹ������ݹ�
            if (check[i] != -1)
            {
                ret += bfs(pos + 1, bound && (i == nums[pos]), diff || (check[i]==1), nums);
            }
        }
        return memo[pos][bound][diff] = ret;
    }
    int rotatedDigits(int n) {
        vector<int> nums;
        //�����Ȱ�n�����һ��vector������ȥʹ��λ��
        while (n)
        {
            nums.push_back(n % 10);
            n /= 10;
        }
        reverse(nums.begin(), nums.end());
        memset(memo, -1, sizeof(memo));
        int i = 0;
        //ʵ��һ���Ӻ�����������ǵ�ǰλ�ã����Ƿ����߷�(���ǰ�涼�����߷ŵģ���ôposλ����Ҫ�ܵ����ƣ���֮����Ҫ)���Ƿ��п���ת����
        int ret = bfs(0, true, false,nums);
        return ret;
    }
private:
    //����Ƿ����޷���ת����
    static int check[10];
    //��һ����ʾ����λ�����ڶ��͵�����ʾtrue or false 
    int memo[5][2][2];
};
int Solution::check[10] = { 0, 0, 1, -1, -1, 1, 1, -1, 0, 1 };
class Solution2 {
public:
    int bfs(int pos, bool bound, bool diff, vector<int> nums)
    {
        if (pos == nums.size())
            return diff; //�ٸ����������n=10����һλ��0 -> bound=false,1->diff=false->2->diff->true��������ǿ���ת����¼һ��
        if (memo[pos][bound][diff] != -1) //�����ҹ���ͬ��
            return memo[pos][bound][diff];
        int ret = 0;//����������
        for (int i = 0; i <= (bound ? nums[pos] : 9); ++i)
        {
            if (check[i] != -1)//���п��޵�ֻ�Ǽ����˼����ж�
            {
                ret += bfs(pos + 1, bound && (i == nums[pos]), diff || check[i] == 1, nums);
            }
        }
        return memo[pos][bound][diff] = ret;
    }
    int rotatedDigits(int n) {
        vector<int> nums;
        //�����Ȱ�n�����һ��vector������ȥʹ��λ��
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
    //����Ƿ����޷���ת����
    static int check[10];
    //��һ����ʾ����λ�����ڶ��͵�����ʾtrue or false 
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