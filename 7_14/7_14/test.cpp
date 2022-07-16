//#include<iostream>
//#include<vector>
//#include<cmath>
//using namespace std;
////完全数
//void Get_Perfect_Num(int n, int& count)
//{
//    vector<int> arr;
//    for (int i = 1; i <= pow(n, 0.5); ++i)
//    {
//        if (n % i == 0)
//        {
//            arr.push_back(i);
//            arr.push_back(n / i);
//        }
//    }
//    int sum = 0;
//    for (int i = 0; i < arr.size(); ++i)
//    {
//        if (arr[i] != n)
//        {
//            sum += arr[i];
//        }
//    }
//    if (sum == n)
//        count++;
//}
//int main()
//{
//    int n;
//    int count = 0;
//    cin >> n;
//    for (int i = 1; i <= n; ++i)
//    {
//        Get_Perfect_Num(i, count);
//    }
//    cout << count << endl;
//    return 0;
//}
//

//扑克牌大小
#include<iostream>
#include<vector>
#include<string>
using namespace std;
static vector<string> vs = { "0","0","0","3","4","5","6","7","8","9","10","J","Q","K","A","2","joker","JOKER" };
void Switch(string& st, vector<int>& vi)
{
    vector<string> vvs;
    vvs.resize(5);
    int i = 0;
    while (!st.empty())
    {
        size_t sz = st.find(' ');
        if (sz == string::npos)
        {
            vvs[i] += st;
            st.clear();
        }
        vvs[i]+=st.substr(0, sz);
        st.erase(0, sz + 1);
        ++i;
    }
    for (int i = 0; i < vvs.size(); ++i)
    {
        for (int j = 0; j < vs.size(); ++j)
        {
            if (vvs[i] == vs[j])
            {
                vi.push_back(j);
            }
        }
    }
}
int GetMaxHands(string one_hands, string two_hands)
{
    vector<int> one_vi;
    vector<int> two_vi;
    Switch(one_hands, one_vi);
    Switch(two_hands, two_vi);
    //里面存的值就对了
    //四个的话只有可能是炸弹，两个可能是对子，可能是王炸
    int one_sz = one_vi.size();
    int two_sz = two_vi.size();
    //用第一个去匹配第二个
    if (one_sz == 1)
    {
        if (two_sz == 1)
        {
            if (one_vi[0] > two_vi[0])
                return 1;
            else
            {
                return 2;
            }
        }
        else if (two_sz == 2)
        {
            if (two_vi[0] == 16 && two_vi[1] == 17)
                return 2;
            else
                return 3;
        }
        else if (two_sz == 4)
        {
            return 2;
        }
        else
            return 3;
    }
    else if (one_sz == 2)
    {
        if (one_vi[0] == 16 && one_vi[1] == 17)
            return 1;
        if (two_sz == 2)
        {
            if (two_vi[0] == 16 && two_vi[1] == 17)
                return 2;
            else if (two_vi[0] > one_vi[0])
                return 2;
            else
                return 1;
        }
        else if (two_sz == 4)
        {
            return 2;
        }
        else
            return 3;
    }
    else if (one_sz == 3)
    {
        if (two_sz == 2)
        {
            if (two_vi[0] == 16 && two_vi[1] == 17)
                return 2;
            else
                return 3;
        }
        else if (two_sz == 3)
        {
            if (two_vi[0] > one_vi[0])
                return 2;
            else
                return 1;
        }
        else if (two_sz == 4)
            return 2;
        else
            return 3;
    }
    else if (one_sz == 4)
    {
        if (two_sz == 2)
        {
            if (two_vi[0] == 16 && two_vi[1] == 17)
                return 2;
            else
                return 1;
        }
        else if (two_sz == 4)
        {
            if (two_vi[0] > one_vi[0])
                return 2;
            else
                return 1;
        }
        else
            return 1;
    }
    else if (one_sz == 5)
    {
    if (two_sz == 2)
    {
        if (two_vi[0] == 16 && two_vi[1] == 17)
            return 2;
        else
            return 1;
    }
    else if (two_sz == 4)
        return 2;
    else if (two_sz == 5)
    {
        if (two_vi[0] > one_vi[0])
            return 2;
        else
            return 1;
    }
    else
        return 3;
    }
    return 3;
}
int main()
{
    string st;
    getline(cin, st);
    string One_Hands;
    string Two_Hands;
    size_t sz = st.find('-');
    One_Hands = st.substr(0, sz);
    st.erase(0, sz + 1);
    Two_Hands = st;
    //如果返回值是1则输出one的，是2输出two的是3输出error
    int ret=GetMaxHands(One_Hands, Two_Hands);
    if (ret == 1)
        cout << One_Hands << endl;
    else if (ret == 2)
        cout << Two_Hands << endl;
    else
        cout << "ERROR" << endl;
    return 0;
}