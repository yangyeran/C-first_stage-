#include<iostream>
#include<string>
#include<vector>
using namespace std;
int main()
{
    int n;
    int len = 0, lex = 0;//lenΪ0�����ǰ��ճ��ȣ�lexΪ0�����ǰ����ֵ�
    cin >> n;
    vector<string> vs;
    vector<int> sz;
    for (int i = 0; i < n; ++i)
    {
        string st;
        cin >> st;
        vs.push_back(st);
        sz.push_back(vs[i].size());
    }
    for (int i = 0; i < n - 1; ++i)
    {
        if (vs[i].front() <= vs[i + 1].front())
        {
            if (i + 1 == n - 1 )
                lex = 1;
        }
        else
            break;
    }
    for (int i = 0; i < n - 1; ++i)
    {
        if (sz[i] <= sz[i + 1])
        {
            if (i + 1 == n - 1)
                len = 1;
        }
        else
            break;
    }
    for (int i = 0; i < n - 1; ++i)
    {
        if (vs[i].front() >= vs[i + 1].front())
        {
            if (i + 1 == n - 1)
                lex = 1;
        }
        else
            break;
    }
    for (int i = 0; i < n - 1; ++i)
    {
        if (sz[i] >= sz[i + 1])
        {
            if (i + 1 == n - 1)
                len = 1;
        }
        else
            break;
    }
    if (len == 1 && lex == 1)
        cout << "both" << endl;
    else if (len == 1 && lex == 0)
        cout << "lengths" << endl;
    else if (len == 0 && lex == 1)
        cout << "lexicographically" << endl;
    else if (len == 0 && lex == 0)
        cout << "none" << endl;
    return 0;
}
//��С������
#include<iostream>
using namespace std;
int max_factor(int x, int y)
{
    if (x < y)
        swap(x, y);
    while (y)
    {
        //ŷ�����
        int z = x % y;
        x = y;
        y = z;
    }
    return x;
}
int main()
{
    int A, B;
    cin >> A >> B;
    int max = max_factor(A, B);
    int ret = A * B / max;
    cout << ret << endl;
    return 0;
}