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
            //����ѹջ�洢��ȥ
            while (cur)
            {
                st.push(cur);
                cur = cur->left;
            }
            TreeNode* top = st.top();
            st.pop();
            v.push_back(top->val);
            //�൱�ڸĳ���������
            cur = top->right;
        }
        return v;
	}
};
int main()
{
}