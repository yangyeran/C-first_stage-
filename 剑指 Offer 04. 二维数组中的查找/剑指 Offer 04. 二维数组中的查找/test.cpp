#include<iostream>
#include<vector>
using namespace std;
//bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
//    if (matrix.empty() || matrix[0].empty())
//        return false;
//    int record_i = 0;
//    int record_j = 0;
//    for (int i = 0; i < matrix.size(); ++i)
//    {
//        if (matrix[i][matrix[i].size() - 1] < target)
//        {
//            ++record_i;
//        }
//        else
//        {
//            break;
//        }
//    }
//    for (int i = 0; i < matrix[0].size(); ++i)
//    {
//        if (matrix[matrix.size() - 1][i] < target)
//        {
//            ++record_j;
//        }
//        else
//        {
//            break;
//        }
//    }
//    for (int i = record_i; i < matrix.size(); ++i)
//    {
//        for (int j = record_j; j < matrix[i].size(); ++j)
//        {
//            if (matrix[i][j] == target)
//            {
//                return true;
//            }
//        }
//    }
//    return false;
//}
bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
    int n = matrix.size() - 1;
    int m = matrix[0].size() - 1;
    int i = 0, j = m;
    while (i <= n && j >= 0)
    {
        //从右上角往下看，可以看做是小在左大在右搜索二叉树
        //对应到数组中就是小在左大在下
        if (matrix[i][j] > target)
        {
            --j;
        }
        else if (matrix[i][j] < target)
        {
            ++i;
        }
        else
        {
            return true;
        }
    }
    return false;
}
int main()
{
    vector<vector<int>> vvi{ {-5} };
    //vector<vector<int>> vvi{ {1,   4,  7, 11, 15} ,{2,   5,  8, 12, 19 },{3,   6,  9, 16, 22},{10, 13, 14, 17, 24},{18, 21, 23, 26, 30 } };
    cout << findNumberIn2DArray(vvi, -5) << endl;
}