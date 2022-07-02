//#include<iostream>
//using namespace std;
//int main()
//{
//	int arr[][3] = { 10,20,30,40,50,60 };
//	int(*p)[3];
//	p = arr;
//	cout << p[0][0] << "," << *(p[0] + 1) << "," << (*p)[2] << endl;
//	return 0;
//}
//牛客统计回文
//#include<iostream>
//#include<string>
//using namespace std;
//int main()
//{
//    string A;
//    string B;
//    getline(cin, A);
//    getline(cin, B);
//    int count = 0;
//    int sz = A.size() + 1;
//    while (sz)
//    {
//        string st(A);
//        st.insert(sz - 1, B);
//        int i = 0, j = st.size() - 1;
//        while (i < j && st[i] == st[j])
//        {
//            ++i;
//            --j;
//        }
//        if (i >= j)
//        {
//            ++count;
//        }
//        --sz;
//    }
//    cout << count << endl;
//    return 0;
//}
//连续最大子数组和
#include<iostream>
#include<vector>
using namespace std;
int main()
{
    vector<int> nums;
    int N;
    cin >> N;
    for (int i = 0; i < N; ++i)
    {
        int j = 0;
        cin >> j;
        nums.push_back(j);
    }
    int x = nums[0];
    int y = x, maxsum = y;
    for (int i = 1; i < nums.size(); ++i)
    {
        y = max(x + nums[i], nums[i]);
        maxsum = max(y, maxsum);
        x = y;
    }
    cout << maxsum << endl;
    return 0;
}