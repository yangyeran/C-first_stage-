#include<iostream>
#include<string>
using namespace std;
class Solution {
public:
    string replaceSpace(string s) {
        int pos = s.find(' ');
        while (pos != string::npos)
        {
            s.erase(pos, 1);
            s.insert(pos, "%20");
            pos = s.find(' ');
        }
        return s;
    }
};