//找出字符串中第一个只出现一次的字符
#include<iostream>
#include<string>
using namespace std;
int main()
{
    string s1;
    cin >> s1;
    int arr[26] = { 0 };
    for (size_t i = 0; i < s1.size(); i++)
    {
        //出现次数
        arr[s1[i] - 'a']++;
    }
    int j = 0;
    for (j = 0; j < s1.size(); j++)
    {
        if (arr[s1[j] - 'a'] == 1)
        {
            cout << s1[j] << endl;
            return 0;
        }
    }
    cout << -1 << endl;
    return 0;
}