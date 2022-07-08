//另类加法
class UnusualAdd {
public:
    int addAB(int A, int B) {
        // write code here
        int ret = 0, count = 0;
        while (B != 0)
        {
            ret = A ^ B;
            count = (A & B) << 1;
            A = ret;
            B = count;
        }
        return ret;
    }
};

//走方格的方案数
//主体思路就是递归，因为只能向下或者向右走所以只有俩种选择，要么n--，要么m--
//然后用count来记录一下递归了多少次就行了
#include<iostream>
#include<vector>
using namespace std;
int get_steps(int n, int m, int& count)
{
    if (n == 0 || m == 0)
    {
        ++count;
        return 1;
    }
    else
        return get_steps(n - 1, m, ++count) + get_steps(n, m - 1, ++count);
}
int main()
{
    int n, m;
    int count = 0;
    cin >> n >> m;
    cout << get_steps(n, m, count) << endl;
    return 0;
}