#include<iostream>
#include<stack>
using namespace std;
/*236. ������������������� https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/
����һ��������, �ҵ�����������ָ���ڵ������������ȡ�
�ٶȰٿ�������������ȵĶ���Ϊ���������и��� T �������ڵ� p��q��
����������ȱ�ʾΪһ���ڵ� x������ x �� p��q �������� x ����Ⱦ����ܴ�һ���ڵ�Ҳ���������Լ������ȣ�����*/
struct TreeNode 
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    
};
class Solution1 {
public:
    //����˼·Ҳ���Ǳ�����⣬�ҵ�p��q����λ�ã����ͬΪ������ң����ȵ��ľ��Ǹ��ڵ�
    //���q��p��root��������ôroot��Ϊ��С�ڵ�
    //ȱ������ԣ��ݹ���������̫����������o(n*n)
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
        //�����ջ�û���ҵ��Ǿͻ��˵���һ��
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
        //�洢·���ķ���
        //����������ջ���洢·��
        //�Ӹ��ڵ������Ȼ��ȥ������������ȥ�ҡ�������
        if (root == nullptr)
            return nullptr;
        stack<TreeNode*> stq;
        stack<TreeNode*> stp;
        Find(root, p, stp);
        Find(root, q, stq);
        if (stq.size() < stp.size())
            swap(stq, stp);
        //stq���
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