#include<iostream>
#include<string>
#include<vector>
using namespace std;
//��Ԫ��ϵ���ܱ��̳�
//��̬��ԱҲ�ᱻ�̳У�����ֻ��һ�ݣ�Ҳ��˵��������๲��һ����̬��Ա
//class Person
//{
//public:
//	Person(const string& name, int age)
//		:_name(name)
//		, _age(age)
//	{
//		++count;
//	}
//	void Print()
//	{
//		cout << _name << _age;
//	}
//	string _name="����";
//	static int count;
//	int _age=20;
//private:
//	int _a = 10;
//};
//int Person::count = 0;
//class Student : virtual public Person
//{
//public:
//	//����ĳ�Ա��ʼ�����߲���������ʹ�ø���ĺ��������в�������ֱ�Ӵ���
//	Student(const string& name, int age, int ID)
//		:Person(name, age)
//		, _ID(ID)
//	{}
//	//���������ᱻ������ͳһ�����destructor()
//	//��������͸�������������ͻṹ�����أ��Ӷ������������޶����Ͳ��ܹ�ʹ��
//	//������������������ʱ����Զ����ø������������
//	~Student()
//	{
//		Person::~Person();
//	}
//protected:
//	int _ID;
//};
//class Teacher : virtual public Person
//{
//public:
//protected:
//	int _num;
//};
//class Assistant : public Student,public Teacher
//{
//public:
//protected:
//	int _year;
//};
//�̳з�Ϊ���̳У��Ͷ�̳�
//���̳о���ֻ��һ��ֱ�Ӹ���
// ����class Student : public Person
//һ�����������������������ϵĸ��������̳�
//����class Student : public Person, public Teacher
//���μ̳��Ƕ�̳е�һ�����������					class Person
//								class Student : public Person  class Teacher : public Person  ��̳�����һ���̳�
//									 class  Assistant : public Student,public Teacher 
//										���μ̳л�������ݵ�����Ͷ�����
//									  ��̳п��Խ����������Ͷ����ԣ��ؼ���(virtual)
//											        Personһ��������
//                       ��Assistant��A����һ�������������Student/TeacherҪ�ҵ�Person��Ҫͨ��������е�ƫ�������м���
//													�����Ļ����磺Assistant a; Student s = a;
//int main()
//{
//	cout << (fun());
//	//Student s("����", 20, 11020);
//	//cout << s.count << endl;
//}    




//////////////////////////////////////////////////////

//#include<iostream>
//#include<vector>
//#include<algorithm>
//using namespace std;
//int main()
//{
//	int n;
//	cin >> n;
//	vector<int> arr;
//	for (int i = 0; i < 3 * n; ++i)
//	{
//		int j = 0;
//		cin >> j;
//		arr.push_back(j);
//	}
//	sort(arr.begin(), arr.end());
//	int ret = 0;
//	for (int i = arr.size() - 1 - 1; i > 0; i -= 2)
//	{
//		ret += arr[i];
//	}
//	cout << ret << endl;
//	return 0;
//}


//class Person {
//public:
//	string _name="����";
//	void fun(int age)
//	{
//		_age = age;
//	}
//	void Age(int age)
//	{
//		_age = age;
//	}
//protected:
//	int _age=20;
//private:
//	int _a = 10;
//};
//class Student :public Person {
//public:
//	int num = 100;
//};
//class Person
//{
//protected:
//	string _name; // ����
//	string _sex; // �Ա�
//	int _age; // ����
//};
//class Student : public Person
//{
//public:
//	int _No; // ѧ��
//};
//void Test()
//{
//	Student st;
//	// 1.���������Ը�ֵ���������/ָ��/����
//	Person ps = st;
//	Person* pp = &st;
//	Person& rp = st;
//	//2.��������ܸ�ֵ�����������
//	//st = ps;
//	// 3.�����ָ�����ͨ��ǿ������ת����ֵ���������ָ��
//	pp = &st;
//	Student* ps1 = (Student*)pp; // �������ת��ʱ���Եġ�
//	ps1->_No = 10;
//	pp = &ps;
//	Student* ps2 = (Student*)pp; // �������ת��ʱ��Ȼ���ԣ����ǻ����Խ����ʵ�����
//	ps2->_No = 10;
//}
// �̳��뾲̬��Ա
//class Person 
//{
//public:
//	Person()
//	{
//		++number;
//	}
//	static int number;
//protected:
//	string _name;
//};
//int Person::number = 0;
//class Student : public Person
//{
//public:
//	int id;
//};
//int main()
//{
//	Person p1;
//	Student s1;
//	Student s2;
//	Student s3;
//}

//���μ̳� ��̳йؼ��֣�virtual��
class A 
{
public:
	int _a;
};
class B: virtual public A
{
public:
	int _b;
};
class C: virtual public A
{
public:
	int _c;
};
class D : public B,public C
{
public:
	int _d;
};
int main()
{
	D d;
	//û������̳�ʱ��b����_a,c��Ҳ��_a
	d.B::_a = 1;
	d.C::_a = 2;
	d._b = 3;
	d._c = 4;
	d._d = 5;
	return 0;
}


























