//155. ��Сջ
//���һ��֧�� push ��pop ��top �����������ڳ���ʱ���ڼ�������СԪ�ص�ջ��
//ʵ�� MinStack �� :
//MinStack() ��ʼ����ջ����
//void push(int val) ��Ԫ��val�����ջ��
//void pop() ɾ����ջ������Ԫ�ء�
//int top() ��ȡ��ջ������Ԫ�ء�
//int getMin() ��ȡ��ջ�е���СԪ�ء�
#include<iostream>
#include<stack>
using namespace std;
class MinStack {
    //����˼·���Ƕ�������ջ��һ������ջ������һ������ջԪ�ؽ��бȽϣ����С�ڵ��ھ���minST����
public:
    MinStack() {
        //  Ĭ�ϵĹ���͹�����
    }

    void push(int val) {
        st.push(val);
        if (minST.empty() || minST.top() >= val)
        {
            minST.push(val);
        }
    }

    void pop() {
        if (!minST.empty() && st.top() == minST.top())
        {
            minST.pop();
        }
        st.pop();
    }

    int top() {
        return st.top();
    }

    int getMin() {
        return minST.top();
    }
private:
    stack<int> minST;
    stack<int> st;
};
int main()
{
    MinStack st;
}