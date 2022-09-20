#include<iostream>
#include<stack>
#include<vector>
using namespace std;
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        //×ó¸ùÓÒ
        stack<TreeNode*> st;
        TreeNode* cur = root;
        vector<int> ret;
        if (root == nullptr)
            return ret;
        while (cur || !st.empty())
        {
            while (cur)
            {
                st.push(cur);
                cur = cur->left;
            }
            TreeNode* top = st.top();
            ret.push_back(top->val);
            st.pop();
            if (top->right)
            {
                cur = top->right;
            }
        }
        return ret;
    }
};
int main()
{
}