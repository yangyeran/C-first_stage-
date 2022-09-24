#include<iostream>
#include<vector>
using namespace std;
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    
};
TreeNode* _buidTree(vector<int>& preorder, vector<int>& inorder, int& prei, int inbegin, int inend)
{
    if (inbegin > inend)
        return nullptr;
    TreeNode* root = new TreeNode(preorder[prei]);
    int i = inbegin;
    while (i < inorder.size())
    {
        if (inorder[i] != preorder[prei])
        {
            ++i;
        }
        else
        {
            break;
        }
    }
    ++prei;
    root->left = _buidTree(preorder, inorder, prei, inbegin, i - 1);
    root->right = _buidTree(preorder, inorder, prei, i + 1, inend);
    return root;
}
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    //前序遍历根，中序遍历区间
    int prei = 0;
    // 双闭区间
    return _buidTree(preorder, inorder, prei, 0, inorder.size() - 1);
}
int main()
{
}