#include<iostream>
#include<vector>
using namespace std;
vector<int> decrypt(vector<int>& code, int k) {
    vector<int> ret;
    ret.resize(code.size());
    for (int i = 0; i < code.size(); ++i)
    {
        if (k > 0)
        {
            int sum = 0;
            for (int j = 1; j <= k; ++j)
            {
                sum += code[(i + j) % code.size()];
            }
            ret[i] = sum;
        }
        else if (k < 0)
        {
            int sum = 0;
            for (int j = 1; j <= abs(k); ++j)
            {
                if (i - j >= 0)
                {
                    sum += code[(i - j) % code.size()];
                }
                else
                {
                    sum += code[code.size() + (i - j)];
                }
            }
            ret[i] = sum;
        }
        else
        {
            ret[i] = 0;
        }
    }
    return ret;
}
int main()
{
    vector<int> code{ 10,5,7,7,3,2,10,3,6,9,1,6 };
    decrypt(code, -4);
}