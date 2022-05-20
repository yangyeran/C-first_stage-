//���������������У���һ�����б�ʾջ��ѹ��˳�����жϵڶ��������Ƿ����Ϊ��ջ�ĵ���˳�򡣼���ѹ��ջ���������־�����ȡ�
//��������1, 2, 3, 4, 5��ĳջ��ѹ��˳������4, 5, 3, 2, 1�Ǹ�ѹջ���ж�Ӧ��һ���������У���4, 3, 5, 1, 2�Ͳ������Ǹ�ѹջ���еĵ������С�
//1. 0 <= pushV.length == popV.length <= 1000
//2. - 1000 <= pushV[i] <= 1000
//3. pushV ���������־�����ͬ
#include<iostream>
#include<vector>
#include<stack>
using namespace std;
class Solution {
    //˼·���Ƚ��бȽ�ѹ���ֵ�뵯����ֵ�಻��ͬ���������ͬ��һֱ����
    //ֱ����ͬ����֮ͬ���Ȱ���ͬ��Ԫ����ջ��Ȼ��ʼ�����ĳ�ջ��ֱ���뵯����ֵ��ͬ
    //��ʱ�۲�pushV��û�е���β�����û�е���β�����������裬�������β�Ǿ����޷��γ�
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
        //���������Ѿ�������
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