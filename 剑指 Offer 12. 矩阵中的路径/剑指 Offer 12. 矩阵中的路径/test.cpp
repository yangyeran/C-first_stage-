#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    bool dfs(vector<vector<char>>& board, string word, vector<vector<int>>& check, int i, int j, int start)
    {
        if (start == word.size())
            return true;
        if (i < 0 || j < 0 || i == board.size() || j == board[0].size() || check[i][j] == 1)
            return false;
        bool ans = false;
        if (board[i][j] == word[start])
        {
            check[i][j] = 1;
            //迭代去找
            ans = dfs(board, word, check, i + 1, j, start + 1) ||
                dfs(board, word, check, i, j + 1, start + 1) ||
                dfs(board, word, check, i - 1, j, start + 1) ||
                dfs(board, word, check, i, j - 1, start + 1);
        }
        //如果某一条路径不正确，要把变成1的还原成0
        if (ans == false)
        {
            check[i][j] = 0;
        }
        return ans;
    }
    bool exist(vector<vector<char>>& board, string word) {
        if (board.size() == 0 || board[0].size() == 0)
            return false;
        int m = board.size();
        int n = board[0].size();
        vector<vector<int>> check;
        check.resize(m);
        for (int z = 0; z < m; ++z)
        {
            check[z].resize(n, 0);
        }
        //给一个检测数组，如果值为1则为找过了，为0则是没找过
        for (int i = 0; i < board.size(); ++i)
        {
            for (int j = 0; j < board[0].size(); ++j)
            {
                if (dfs(board, word, check, i, j, 0))
                {
                    return true;
                }
            }
        }
        return false;
    }
};
int main()
{
    vector<vector<char>> board{ {'A','B','C','E'},{'S','F','E','S'},{'A','D','E','E'} };
    cout<<Solution().exist(board, "ABCESEEEFS");
}