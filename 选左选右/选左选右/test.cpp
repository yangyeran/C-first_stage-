//给出N个数排成一排。每次只能从最左边或者最右边去拿数字，两个人每次都拿两边最大的一个数，A先拿，问A先手最多能拿到多少分
#include<iostream>
#include<vector>
using namespace std;
int main()
{
	int N = 0,j=0;
	int x = 0;
	cin >> N;
	vector<int> arr;
	while (cin >> j)
	{
		static int i = 0;
		arr.push_back(j);
		++i;
		if (i == N)
			break;
	}
	while (!arr.empty())
	{
		//flag 控制的是如果N为偶数，那么最后一个是另外一个人拿，但是如果是奇数的话最后一个是A拿
		int flag = N % 2;//如果是0就是偶数，是1就是奇数
		if (arr.front() < arr.back())
		{
			x += arr.back();
			arr.pop_back();
			if (!arr.empty() && arr.front() < arr.back())
			{
				arr.pop_back();
			}
			else if (!arr.empty() && arr.front() > arr.back())
			{
				arr.erase(arr.begin());
			}
			if (arr.size() == 1)
			{
				if (flag == 1)
					x += arr.front();
				arr.pop_back();
			}
		}
		else
		{
			x += (arr.front());
			arr.erase(arr.begin());
			if (!arr.empty() && arr.front() < arr.back())
			{
				arr.pop_back();
			}
			else if (!arr.empty() && arr.front() > arr.back())
			{
				arr.erase(arr.begin());
			}
			if (arr.size() == 1)
			{
				if (flag == 1)
					x += arr.front();
				arr.pop_back();
			}
		}
	}
	cout << x << endl;
	return 0;
}
//#include<iostream>
//#include<vector>
//using namespace std;
//int main()
//{
//	int N = 0, j = 0;
//	int x = 0;
//	cin >> N;
//	vector<int> arr;
//	while (cin >> j)
//	{
//		static int i = 0;
//		arr.push_back(j);
//		++i;
//		if (i == N)
//			break;
//	}
//	int flag = N % 2;
//	while (!arr.empty())
//	{
//		vector<int>::iterator begin = arr.begin();
//		vector<int>::iterator end = arr.end();
//		if (*begin < *(end-1))
//		{
//			x += *(end - 1);
//			arr.pop_back();
//			end = arr.end();
//			if (!arr.empty() && (*begin < *(end-1)) )
//			{
//				arr.pop_back();
//				end = arr.end();
//			}
//			else if (!arr.empty() && (*begin > *(end-1)))
//			{
//				//erase是挪动删除，如果是头删的话，尾部的end也需要更新，否则就会导致迭代器失效
//				begin = arr.erase(arr.begin());
//				end = arr.end();
//			}
//			if (arr.size() == 1)
//			{
//				if (flag == 1)
//					x += arr.front();
//				arr.pop_back();
//			}
//		}
//		else
//		{
//			x += (*begin);
//			begin = arr.erase(arr.begin());
//			end = arr.end();
//			if (!arr.empty() && (*begin < *(end-1)))
//			{
//				arr.pop_back();
//				end = arr.end();
//			}
//			else if (!arr.empty() && (*begin > *(end-1)))
//			{
//				begin = arr.erase(arr.begin());
//				end = arr.end();
//			}
//			if (arr.size() == 1)
//			{
//				if (flag == 1)
//					x += arr.front();
//				arr.pop_back();
//			}
//		}
//	}
//	cout << x << endl;
//	return 0;
//}