#include<iostream>
#include<vector>
#include<stack>
using namespace std;
  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  };
 
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        TreeNode* cur = root;
        TreeNode* prev = nullptr;
        stack<TreeNode*> st;
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
            //左子树压入栈了
            TreeNode* top = st.top();
            //右子树访问过了就访问
            if (top->right == nullptr || prev == top->right)
            {
                ret.push_back(top->val);
                prev = top;
                st.pop();
            }
            else//右子树没有访问过就走它的右子树
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