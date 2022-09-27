#include<iostream>
#include<string>
using namespace std;
class Solution {
public:
    bool CheckPermutation(string s1, string s2) {
        //������������һ���Ǵ�С��ȵģ��ù�ϣ����ӳ���һ���ַ�����Ȼ�����s2
        if (s1.size() != s2.size())
            return false;
        for (auto e : s1)
        {
            hash1[e - 'a'] = 1;
            hash2[e - 'a']++;
        }
        for (auto e : s2)
        {
            if (hash1[e - 'a'] != 1)
                return false;
            else
            {
                --hash2[e - 'a'];
            }
        }
        for (auto e : hash2)
        {
            if (e)
                return false;
        }
        return true;
    }
private:
    //��һ���ж��ڲ��ڣ��ڶ����ж��ж��ٸ�
    int hash1[27] = { 0 };
    int hash2[27] = { 0 };
};
int main()
{
    cout<< Solution().CheckPermutation("abc", "bcd")<<"  "<< Solution().CheckPermutation("abc", "bac");;
    return 0;
}