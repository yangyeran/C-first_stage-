//����N�����ų�һ�š�ÿ��ֻ�ܴ�����߻������ұ�ȥ�����֣�������ÿ�ζ�����������һ������A���ã���A����������õ����ٷ�
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
		//flag ���Ƶ������NΪż������ô���һ��������һ�����ã���������������Ļ����һ����A��
		int flag = N % 2;//�����0����ż������1��������
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
//				//erase��Ų��ɾ���������ͷɾ�Ļ���β����endҲ��Ҫ���£�����ͻᵼ�µ�����ʧЧ
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