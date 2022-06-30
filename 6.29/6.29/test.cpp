#include<iostream>
#include<string>
#include<vector>
using namespace std;
int main()
{
    string st, ret;
    getline(cin, st);
    int count = 0;
    for (int i = 0; i < st.size();)
    {
        int flag = 0;
        while (i < st.size() && (st[i] <= '0' || st[i] >= '9'))
        {
            ++i;
        }
        //必然是一个数字字符
        while (i < st.size() && (st[i] >= '0' && st[i] <= '9'))
        {
            ++flag;
            ++i;
        }
        if (flag > count)
        {
            ret = st.substr(i - flag, flag );
            count = flag;
        }
    }
    cout << ret << endl;
    return 0;
}