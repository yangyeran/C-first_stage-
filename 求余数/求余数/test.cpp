#include<iostream>
#include<string>
using namespace std;
void NumSwitch(int n, int m, string& str)
{
    string tmp = to_string(n);
    while (m > 0)
    {
        str += tmp;
        --m;
    }
    cout << str << endl;
}
int main()
{
    int n, m, k;
    string str;
    cin >> n >> m >> k;
    NumSwitch(n, m, str);
    return 0;
}