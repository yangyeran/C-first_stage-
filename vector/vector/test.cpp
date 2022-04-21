#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
void fun1()
{
	vector<int> arr1;
	vector<int> arr2 = { 1,2,3,4,5 };
	vector<int> arr3(arr2);
	vector<int> arr4(5,0);
	//������õ�����ʵ�ֵ�
	string std("hello");
	vector<char> ch1(std.begin(), std.end());
	auto it = arr4.begin();
	while (it != arr4.end())
	{
		*it += 3;
		++it;
	}
	for (vector<char>::iterator it = ch1.begin(); it != ch1.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
	for (vector<int>::reverse_iterator it = arr3.rbegin(); it != arr3.rend(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
	//for (auto it = ch1.begin(); it != ch1.end(); ++it)
	//{
	//	cout << *it << " ";
	//}
	//cout << endl;
	//for (auto it = arr3.rbegin(); it != arr3.rend(); ++it)
	//{
	//	cout << *it << " ";
	//}
	//cout << endl;
}
void fun2()
{
	//size capacity empty reserve rsize
	vector<int> arr1 = {1,2,3,4,5,6,7,8,9};
	vector<int> arr2;
	cout << "size->" << arr1.size() << endl;
	cout << "capacity->" << arr1.capacity() << endl;
	//ֻ�ܿ��ռ䲻�ܳ�ʼ��
	//arr2.reserve(10);
	arr2.resize(10);
	cout << "size->" << arr2.size() << endl;
	cout << "capacity->" << arr2.capacity() << endl;
	//���Գ�ʼ��Ҳ���Բ���ʼ��
	arr1.resize(5,2);
	cout << "size->" << arr1.size() << endl;
	cout << "capacity->" << arr1.capacity() << endl;
	arr1.resize(20);
	cout << "size->" << arr1.size() << endl;
	cout << "capacity->" << arr1.capacity() << endl;
	//cout << "arr1.empty->" << arr1.empty() <<"   " << "arr2.empty()->" << arr2.empty() << endl;
}
void fun3()
{
	//push_back  push_pop  find  insert  erase  swap  operator[]  assign  clear
	vector<int>arr1;
	//β��һ������
	arr1.push_back(1);
	arr1.push_back(2);
	arr1.push_back(3);
	arr1.push_back(4);
	arr1.push_back(5);
	//�õ�����ȥ����
	for (vector<int>::iterator it = arr1.begin(); it != arr1.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
	//��ߴ����ǵ��������ұ���Ҫ���������
	arr1.insert(arr1.begin() + 3, 6);
	arr1.insert(arr1.begin() + 3, 7);
	for (vector<int>::iterator it = arr1.begin(); it != arr1.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
	//βɾһ�����ݣ�û�в���ֱ�ӵ��ü���
	arr1.pop_back();
	arr1.pop_back();
	for (vector<int>::iterator it = arr1.begin(); it != arr1.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
	//��������λ��
	arr1.erase(arr1.end()-2);
	for (vector<int>::iterator it = arr1.begin(); it != arr1.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
	vector<int> arr2;
	swap(arr1, arr2);
	swap(arr2[0], arr2[3]);
	for (vector<int>::iterator it = arr1.begin(); it != arr1.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
	for (vector<int>::iterator it = arr2.begin(); it != arr2.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
	arr1 = { 9,8,7,6,5 };
	for (vector<int>::iterator it = arr1.begin(); it != arr1.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
	arr1.clear();
	for (vector<int>::iterator it = arr1.begin(); it != arr1.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
}
void fun4()
{
	//assign
	vector<int>arr1 = { 9,8,7,6,5 };
	vector<int>arr2 = { 0,1,2,3,4,10,11,12 };
	arr1.assign(arr2.begin(), arr2.end());
	for (vector<int>::iterator it = arr1.begin(); it != arr1.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
	arr1.assign(8, 0);
	for (vector<int>::iterator it = arr1.begin(); it != arr1.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
}
int main()
{
	fun4();
}