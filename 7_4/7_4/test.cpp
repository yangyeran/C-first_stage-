#include<iostream>
#include<vector>
#include<string>
#include<stack>
#include<cmath>
using namespace std;
//int Fibonacci(int n)
//{
//    if (n == 1 || n == 2)
//        return 1;
//    else
//        return Fibonacci(n - 1) + Fibonacci(n - 2);
//}
//int main()
//{
//    int N, i = 1;
//    vector<int> arr={0};
//    cin >> N;
//    while (arr.back() < N)
//    {
//        arr.push_back(Fibonacci(i));
//        ++i;
//    }
//    int ret1 = abs(N - arr.back());
//    int ret2 = abs(N - arr[arr.size() - 2]);
//    if (ret1 < ret2)
//        cout<<ret1<<endl;
//    else
//        cout<<ret2<<endl;
//    return 0;
//}
bool chkParenthesis(string A, int n) {
   // write code here
   stack<char> st;
   for (int i = 0; i < n; ++i)
   {
        if (A[i] != '(' && A[i] != ')')
            return false;
         if (A[i] == '(')
            st.push('(');
        else if (A[i] == ')')
        {
            if (!st.empty())
               st.pop();
            else
               return false;
        }
   }
   if (!st.empty())
       return false;
   else
       return true;
}
int main()
{
   cout<< chkParenthesis("()()()()()", 10)<<endl;
   return 0;
}