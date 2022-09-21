#include<iostream>
#include<vector>
using namespace std;
  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  };
 
    TreeNode* _buildTree(vector<int>& preorder, vector<int>& inorder, int& prei, int inbegin, int inend)
    {
        if (inbegin > inend)
            return nullptr;
        TreeNode* root = new TreeNode(preorder[prei]);
        int i = inbegin;
        while (preorder[prei] != inorder[i])
        {
            ++i;
        }
        ++prei;
        root->left = _buildTree(preorder, inorder, prei, inbegin, i - 1);
        root->right = _buildTree(preorder, inorder, prei, i + 1, inend);
        return root;
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        //因为前序是根左右，所以每一个遍历每一个节点
        //中序是左根右，通过前序的值来判断中序的区间
        int prei = 0;
        //传个闭区间
        return _buildTree(preorder, inorder, prei, 0, inorder.size() - 1);
    }
int main()
{
    vector<int> preorder = { 3,9,20,15,7 };
    vector<int> ininorder = { 9,3,15,20,7 };
    buildTree(preorder, ininorder);
}