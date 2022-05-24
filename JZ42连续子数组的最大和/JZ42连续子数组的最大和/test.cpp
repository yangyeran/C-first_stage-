#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    //空间和时间都是O(n)
    int FindGreatestSumOfSubArray(vector<int> array)
    {
        //tmp存的是第i位之和的最大值
        vector<int> tmp(array.size(), 0);
        tmp[0] = array[0];
        int maxsum = tmp[0];
        for (int i = 1; i < array.size(); ++i)
        {
            tmp[i] = max(tmp[i - 1] + array[i], array[i]);
            maxsum = max(maxsum, tmp[i]);
        }
        return maxsum;
    }
    //动态规划算法的基本思想是：将待求解的问题分解成若干个相互联系的子问题，先求解子问题，然后从这些子问题的解得到原问题的解；
    //对于重复出现的子问题，只在第一次遇到的时候对它进行求解，并把答案保存起来，让以后再次遇到时直接引用答案，不必重新求解。
    //动态规划算法将问题的解决方案视为一系列决策的结果
    //时间O(n)空间O(1)
    int _FindGreatestSumOfSubArray(vector<int> array)
    {
        int x = array[0];
        int y = x,maxsum=y;
        for (int i = 1; i < array.size(); ++i)
        {
            y = max(x + array[i], array[i]);
            maxsum = max(maxsum, y);
            x = y;
        }
        return maxsum;
    }
};