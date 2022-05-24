#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    //�ռ��ʱ�䶼��O(n)
    int FindGreatestSumOfSubArray(vector<int> array)
    {
        //tmp����ǵ�iλ֮�͵����ֵ
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
    //��̬�滮�㷨�Ļ���˼���ǣ�������������ֽ�����ɸ��໥��ϵ�������⣬����������⣬Ȼ�����Щ������Ľ�õ�ԭ����Ľ⣻
    //�����ظ����ֵ������⣬ֻ�ڵ�һ��������ʱ�����������⣬���Ѵ𰸱������������Ժ��ٴ�����ʱֱ�����ô𰸣�����������⡣
    //��̬�滮�㷨������Ľ��������Ϊһϵ�о��ߵĽ��
    //ʱ��O(n)�ռ�O(1)
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