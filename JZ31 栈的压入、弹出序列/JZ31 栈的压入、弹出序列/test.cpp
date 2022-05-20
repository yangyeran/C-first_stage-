//输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否可能为该栈的弹出顺序。假设压入栈的所有数字均不相等。
//例如序列1, 2, 3, 4, 5是某栈的压入顺序，序列4, 5, 3, 2, 1是该压栈序列对应的一个弹出序列，但4, 3, 5, 1, 2就不可能是该压栈序列的弹出序列。
//1. 0 <= pushV.length == popV.length <= 1000
//2. - 1000 <= pushV[i] <= 1000
//3. pushV 的所有数字均不相同
#include<iostream>
#include<vector>
#include<stack>
using namespace std;
class Solution {
    //思路：先进行比较压入的值与弹出的值相不相同，如果不相同就一直插入
    //直到相同，相同之后先把相同的元素入栈，然后开始持续的出栈，直到与弹出的值不同
    //这时观察pushV有没有到结尾，如果没有到结尾继续上述步骤，如果到结尾那就是无法形成
public:
    bool IsPopOrder(vector<int> pushV, vector<int> popV) {
        int pushi = 0, popi = 0;
        stack<int> st;
        while (pushi < pushV.size())
        {
            if (st.empty() || st.top() != popV[popi])
            {
                st.push(pushV[pushi]);
                ++pushi;
            }
            while (!st.empty() && st.top() == popV[popi])
            {
                st.pop();
                ++popi;
            }
        }
        //到这这里已经结束了
        if (!st.empty())
            return false;
        return true;
    }
};
int main()
{
    vector<int> ve1 ={1,2,3,4,5};
    vector<int> ve2 = { 5,4,3,2,1 };
    Solution().IsPopOrder(ve1,ve2);
}