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
 
class Solution {
public:
    TreeNode* _buildTree(vector<int>& inorder, vector<int>& postorder, int& posi, int inbegin, int inend)
    {
        if (inbegin > inend)
        {
            return nullptr;
        }
        TreeNode* root = new TreeNode(postorder[posi]);
        int i = inbegin;
        while (postorder[posi] != inorder[i])
        {
            ++i;
        }
        --posi;
        //后面俩个位置不能颠倒，要知道后序遍历从最后一个节点开始找
        //往前迭代的时候是先找的右子树的节点在找的左子树的节点，如果颠倒会导致找不到从而产生越界，引发内存错误
        root->right = _buildTree(inorder, postorder, posi, i + 1, inend);
        root->left = _buildTree(inorder, postorder, posi, inbegin, i - 1);
        return root;
    }
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int posi = postorder.size() - 1;
        return _buildTree(inorder, postorder, posi, 0, inorder.size() - 1);
    }
};
int main()
{
    vector<int> postorder = { 9,15,7,20,3 };
    vector<int> inorder = { 9,3,15,20,7 };
    Solution().buildTree(inorder, postorder);
}