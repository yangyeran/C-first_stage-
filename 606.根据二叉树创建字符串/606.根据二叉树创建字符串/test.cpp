#include<iostream>
#include<string>
using namespace std;
//给你二叉树的根节点 root ，请你采用前序遍历的方式，将二叉树转化为一个由括号和整数组成的字符串，返回构造出的字符串。
//空节点使用一对空括号对 "()" 表示，转化后需要省略所有不影响字符串与原始二叉树之间的一对一映射关系的空括号对。
//来源：力扣（LeetCode）
//链接：https ://leetcode.cn/problems/construct-string-from-binary-tree
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
    string tree2str(TreeNode* root) {
        string str;
        if (root == nullptr)
            return str;
        str += to_string(root->val);
        //分为几种情况，如果右节点为空肯定不需要括号，但是左节点为空就需要分类讨论
        if (root->left || root->right)//只有两边为空不需要输入括号 
        {
            str += '(';
            str += tree2str(root->left);
            str += ')';
        }
        if (root->right)
        {
            str += '(';
            str += tree2str(root->right);
            str += ')';
        }
        return str;
    }
};