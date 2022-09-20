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
            //������ѹ��ջ��
            TreeNode* top = st.top();
            //���������ʹ��˾ͷ���
            if (top->right == nullptr || prev == top->right)
            {
                ret.push_back(top->val);
                prev = top;
                st.pop();
            }
            else//������û�з��ʹ���������������
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