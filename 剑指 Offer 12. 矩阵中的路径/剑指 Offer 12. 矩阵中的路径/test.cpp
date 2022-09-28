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
            //����ȥ��
            ans = dfs(board, word, check, i + 1, j, start + 1) ||
                dfs(board, word, check, i, j + 1, start + 1) ||
                dfs(board, word, check, i - 1, j, start + 1) ||
                dfs(board, word, check, i, j - 1, start + 1);
        }
        //���ĳһ��·������ȷ��Ҫ�ѱ��1�Ļ�ԭ��0
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
        //��һ��������飬���ֵΪ1��Ϊ�ҹ��ˣ�Ϊ0����û�ҹ�
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