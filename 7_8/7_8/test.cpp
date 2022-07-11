#include<iostream>
using namespace std;
//最近的公共祖先
class LCA {
public:
    int getLCA(int a, int b) {
        // write code here
        if (a > b)
            swap(a, b);
        //直接默认b是大的那个，a是小的那个
        //先大找小
        while (a != 1 && b != 1)
        {
            while (b > a)
            {
                if (b % 2 == 1)
                    b = (b - 1) / 2;
                else if (b % 2 == 0)
                    b /= 2;
            }
            if (b == a)
                return a;
            while (a > b)
            {
                if (a % 2 == 1)
                    a = (a - 1) / 2;
                else if (a % 2 == 0)
                    a /= 2;
            }
            if (b == a)
                return a;
        }
        return 1;
    }
};

//求最大连续的bit数
#include<iostream>
#include<vector>
using namespace std;
int main()
{
    int n, ret = 0;
    cin >> n;
    vector<int> arr;
    while (n)
    {
        arr.push_back(n % 2);
        n /= 2;
    }
    for (int i = 0; i < arr.size(); ++i)
    {
        int count = 0;
        while (arr[i] == 1)
        {
            ++count;
            ++i;
        }
        if (count > ret)
            ret = count;
    }
    cout << ret << endl;
    return 0;
}