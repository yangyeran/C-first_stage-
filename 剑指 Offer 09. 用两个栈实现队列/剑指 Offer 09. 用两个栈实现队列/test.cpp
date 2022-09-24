#include<iostream>
#include<stack>
using namespace std;
class CQueue {
public:
    stack<int> st1;
    stack<int> st2;
    bool empty()
    {
        return st1.empty() && st2.empty();
    }
    void appendTail(int value) {
        st1.push(value);
    }

    int deleteHead()
    {
        if (empty())
            return -1;
        //���st2��Ϊ�վ����ȳ�st2��������ݣ����Ϊ�վͰ�st1���е����������Ƶ�st2��
        int top = 0;
        if (!st2.empty())
        {
            top = st2.top();
            st2.pop();
        }
        else
        {
            while (!st1.empty())
            {
                st2.push(st1.top());
                st1.pop();
            }
            top = st2.top();
            st2.pop();
        }
        return top;
    }
};
int main()
{
}