#include<iostream>
#include<map>
#include<string>
#include<math.h>
using namespace std;
int getKthMagicNumber(int k) {
    //只有最小的才会更新数据
    int* nums = new int[k];
    nums[0] = 1;
    int index1 = 0, index2 = 0, index3 = 0;
    for (int i = 1; i < k; ++i)
    {
        int Min = min(min( nums[index1] * 3,nums[index2] * 5),nums[index3] * 7);
        //不能是else if下面三段代码有去重
        if (Min == nums[index1] * 3)
            ++index1;
        if (Min == nums[index2] * 5)
            ++index2;
        if (Min == nums[index3] * 7)
            ++index3;
        nums[i] = Min;
    }
    return nums[k - 1];
}
int main()
{
    //cout << " ";
    getKthMagicNumber(10);
}