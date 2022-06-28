#include<iostream>
#include<string>
using namespace std;
int main()
{
    string st, ret;
    getline(cin, st);
    while (!st.empty())
    {
        size_t pos = st.rfind(' ');
        if (pos == string::npos)
        {
            ret += st;
            st.clear();
            break;
        }
        ret += st.substr(pos + 1);
        ret += ' ';
        st.erase(pos);
    }
    cout << ret << endl;
    return 0;
}