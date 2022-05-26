//155. 最小栈
//设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈。
//实现 MinStack 类 :
//MinStack() 初始化堆栈对象。
//void push(int val) 将元素val推入堆栈。
//void pop() 删除堆栈顶部的元素。
//int top() 获取堆栈顶部的元素。
//int getMin() 获取堆栈中的最小元素。
#include<iostream>
#include<stack>
using namespace std;
class MinStack {
    //总体思路就是定义两个栈，一个正常栈，另外一个与入栈元素进行比较，如果小于等于就入minST里面
public:
    MinStack() {
        //  默认的构造就够用了
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