#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
string addStrings(string num1, string num2) {
    int end1 = num1.size() - 1;
    int end2 = num2.size() - 1;
    string retstr;
    int next = 0;
    while (end1 >= 0 || end2 >= 0)
    {
        int n1 = 0;
        if (end1 >= 0)
        {
            n1 = num1[end1] - '0';
            end1--;
        }
        int n2 = 0;
        if (end2 >= 0)
        {
            n2 = num2[end2] - '0';
            end2--;
        }
        int ret = n1 + n2 + next;
        if (ret > 9)
        {
            ret -= 10;
            next = 1;
        }
        else
            next = 0;
        retstr.insert(retstr.begin(), ret + '0');
    }
    if (next == 1)
        retstr.insert(0, 1, '1');
    return retstr;
}
string Divide(string str, int x)
{
    int reminder = 0;
    for (int i = 0; i < str.size(); i++)
    {
        int current = reminder * 10 + str[i] - '0';
        str[i] = current / x + '0';
        reminder = current % x;
    }
    int pos = 0;
    while (str[pos] == '0')
    {
        pos++;
    }
    return str.substr(pos);

}
int ret_k(const vector<int>& a)
{
    int i = 1;
    string sumstr;
    while (i < a.size()-1)
    {
        string num1 = to_string(a[i]);
        sumstr=addStrings(num1, sumstr);
        ++i;
    }
    string div=Divide(sumstr, a.size() - 2);
    return stoi(div);
}
int main()
{
	int n, p;
	cin >> n >> p;
	vector<int> a;
	for (int i = 0; i < n; ++i)
	{
		int num;
		cin >> num;
		a.push_back(num);
	}
	sort(a.begin(), a.end());
	int count = 0;
    int k = ret_k(a);
	for (int i= 0; i < n; ++i)
	{
		if (abs(a[i] - k) <= p)
			++count;
	}
	cout << count << endl;
	return 0;
}