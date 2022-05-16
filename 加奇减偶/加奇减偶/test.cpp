#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main()
{
	int N, count = 0;
	cin >> N;
	vector<int> peng;
	for (int i = 0; i < N; ++i)
	{
		int num;
		cin >> num;
		peng.push_back(num);
	}
	sort(peng.begin(), peng.end());
	vector<int> arr;
	vector<int> ke;
	for (int i = 0,j=0;i <= 2 * N; ++i)
	{
		arr.push_back(i);
		if (i!=0 && i!= peng[j])
		{
			ke.push_back(i);
		}
		if (i >= peng[j])
		{
			++j;
		}
	}
	for (int i = 0; i < peng.size(); ++i)
	{
		static int j = 0;
		while(j < ke.size())
		{
			if (peng[i] < ke[j])
			{
				++count;
				++j;
				break;
			}
			++j;
		}
		if (j == ke.size())
			break;
	}
	cout << count << endl;
	return 0;
}