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
        //��������λ�ò��ܵߵ���Ҫ֪��������������һ���ڵ㿪ʼ��
        //��ǰ������ʱ�������ҵ��������Ľڵ����ҵ��������Ľڵ㣬����ߵ��ᵼ���Ҳ����Ӷ�����Խ�磬�����ڴ����
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