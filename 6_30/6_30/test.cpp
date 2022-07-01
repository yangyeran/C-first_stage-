//#include<iostream>
//#include<algorithm>
//#include<vector>
//using namespace std;
//int main()
//{
//    int M, N;
//    vector<int> ret;
//    char arr[6] = { 'A','B','C','D','E','F' };
//    cin >> M >> N;
//    if (M == 0)
//    {
//        cout << 0 << endl;
//        return 0;
//    }
//    if (N <= 10)
//    {
//        while (M)
//        {
//            int count = M % N;
//            ret.push_back(count);
//            M /= N;
//        }
//        reverse(ret.begin(), ret.end());
//        for (auto e : ret)
//        {
//            cout << e;
//        }
//    }
//    else//10进制以上的
//    {
//        while (M)
//        {
//            int count = M % N;
//            ret.push_back(count);
//            M /= N;
//        }
//        reverse(ret.begin(), ret.end());
//        for (auto e : ret)
//        {
//            if (e >= 10)
//            {
//                cout << arr[e - 10];
//                continue;
//            }
//            cout << e;
//        }
//    }
//    return 0;
//}

/////////////////////////////////////////////////////
#include<iostream>
#include<vector>
using namespace std;
int main()
{
    vector<int> num;
    int j, n = 0;
    while (cin >> j)
    {
        num.push_back(j);
        ++n;
        if (n == 4)
            break;
    }
    int A = (num[0] + num[2]) / 2;
    int B = (num[1] + num[3]) / 2;
    int C = (num[3] - num[1]) / 2;
    int B1 = num[2] - A;
    int A1 = num[2] - B;
    if (B1 != B || A1 != A)
    {
        cout << "NO" << endl;
        return 0;
    }
    if (A >= 0 && B >= 0 && C >= 0)
    {
        cout << A << " " << B << " " << C << endl;
    }
    else {
        cout << "NO" << endl;
    }
    return 0;
}