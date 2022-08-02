#include<iostream>
#include<stack>
using namespace std;
/*236. 二叉树的最近公共祖先 https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/
给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。
百度百科中最近公共祖先的定义为：“对于有根树 T 的两个节点 p、q，
最近公共祖先表示为一个节点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”*/
struct TreeNode 
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    
};
class Solution1 {
public:
    //正常思路也就是暴力求解，找到p，q所在位置，如果同为左或者右，最先到的就是父节点
    //如果q，p在root的两边那么root即为最小节点
    //缺点很明显，递归次数，深度太多最坏情况下是o(n*n)
    bool Find(TreeNode* root, TreeNode* x)
    {
        if (root == nullptr)
            return false;
        if (root == x)
            return x;
        return Find(root->left, x) || Find(root->right, x);
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
    {
        if (root == nullptr)
            return nullptr;
        if (root == p || root == q)
            return root;
        bool pright, pleft, qright, qleft;
        pright = Find(root->right, p);
        pleft = !pright;
        qright = Find(root->right, q);
        qleft = !qright;
        if (pleft && qleft)
        {
            return lowestCommonAncestor(root->left, p, q);
        }
        else if (pright && qright)
        {
            return lowestCommonAncestor(root->right, p, q);
        }
        else if ((pleft && qright) || (pright && qleft))
        {
            return root;
        }
        return nullptr;
    }
};
class Solution2 {
public:
    bool Find(TreeNode* root, TreeNode* x, stack<TreeNode*>& st)
    {
        //遇到空还没有找到那就回退到上一层
        if (root == nullptr)
            return false;
        st.push(root);
        if (root == x)
            return true;
        if (Find(root->left, x, st))
            return true;
        if (Find(root->right, x, st))
            return true;
        st.pop();
        return false;
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        //存储路径的方法
        //可以用两个栈来存储路径
        //从根节点出发，然后去左子树右子树去找。。。。
        if (root == nullptr)
            return nullptr;
        stack<TreeNode*> stq;
        stack<TreeNode*> stp;
        Find(root, p, stp);
        Find(root, q, stq);
        if (stq.size() < stp.size())
            swap(stq, stp);
        //stq最大
        for (int i = stq.size() - stp.size(); i > 0; --i)
        {
            stq.pop();
        }
        while (!stq.empty())
        {
            if (stp.top() == stq.top())
                return stp.top();
            else
            {
                stq.pop();
                stp.pop();
            }
        }
        return nullptr;
    }
};
int main()
{}