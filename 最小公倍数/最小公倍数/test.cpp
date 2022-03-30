//最大公倍数用两数相乘除以他们的最大公因数
#include<iostream>
using namespace std;
#include<math.h>
int main()
{
    int x, y;
    cin >> x >> y;
    if (x == 0 || y == 0)
    {
        cout << x << endl;
        return 0;
    }
    int x1 = x, y1 = y;
    int z = y1;
    //求最大公约数
    while (x1 % y1 != 0)
    {
        z = x1 % y1;
        x1 = y1;
        y1 = z;
    }
    cout << ((x * y) / z) << endl;
    return 0;
}