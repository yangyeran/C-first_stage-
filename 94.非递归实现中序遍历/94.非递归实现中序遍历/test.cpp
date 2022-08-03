#include<iostream>
#include<vector>
#include<stack>
using namespace std;
struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}

};
class Solution {
public:
	vector<int> inorderTraversal(TreeNode* root)
	{
        stack<TreeNode*> st;
        TreeNode* cur = root;
        vector<int> v;
        while (cur || !st.empty())
        {
            //左树压栈存储进去
            while (cur)
            {
                st.push(cur);
                cur = cur->left;
            }
            TreeNode* top = st.top();
            st.pop();
            v.push_back(top->val);
            //相当于改成了子问题
            cur = top->right;
        }
        return v;
	}
};
int main()
{
}