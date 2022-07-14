#include<iostream>
#include<string>
#include<vector>
using namespace std;
//友元关系不能被继承
//静态成员也会被继承，但是只有一份，也就说父类和子类共用一个静态成员
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
//	string _name="张三";
//	static int count;
//	int _age=20;
//private:
//	int _a = 10;
//};
//int Person::count = 0;
//class Student : virtual public Person
//{
//public:
//	//父类的成员初始化或者操作，必须使用父类的函数来进行操作不能直接处理
//	Student(const string& name, int age, int ID)
//		:Person(name, age)
//		, _ID(ID)
//	{}
//	//析构函数会被编译器统一处理成destructor()
//	//所以子类和父类的析构函数就会构成隐藏，从而不加作用域限定符就不能够使用
//	//子类析构函数结束的时候会自动调用父类的析构函数
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
//继承分为单继承，和多继承
//单继承就是只有一个直接父类
// 例：class Student : public Person
//一个子类有两个或者两个以上的父类叫做多继承
//例：class Student : public Person, public Teacher
//菱形继承是多继承的一种特殊情况：					class Person
//								class Student : public Person  class Teacher : public Person  虚继承在这一栏继承
//									 class  Assistant : public Student,public Teacher 
//										菱形继承会出现数据的冗余和二义性
//									  虚继承可以解决数据冗余和二义性：关键字(virtual)
//											        Person一般叫虚基类
//                       在Assistant中A放在一个公共区域，如果Student/Teacher要找到Person需要通过虚基表中的偏移量进行计算
//													场景的话例如：Assistant a; Student s = a;
//int main()
//{
//	cout << (fun());
//	//Student s("张三", 20, 11020);
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
//	string _name="张三";
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
//	string _name; // 姓名
//	string _sex; // 性别
//	int _age; // 年龄
//};
//class Student : public Person
//{
//public:
//	int _No; // 学号
//};
//void Test()
//{
//	Student st;
//	// 1.子类对象可以赋值给父类对象/指针/引用
//	Person ps = st;
//	Person* pp = &st;
//	Person& rp = st;
//	//2.基类对象不能赋值给派生类对象
//	//st = ps;
//	// 3.基类的指针可以通过强制类型转换赋值给派生类的指针
//	pp = &st;
//	Student* ps1 = (Student*)pp; // 这种情况转换时可以的。
//	ps1->_No = 10;
//	pp = &ps;
//	Student* ps2 = (Student*)pp; // 这种情况转换时虽然可以，但是会存在越界访问的问题
//	ps2->_No = 10;
//}
// 继承与静态成员
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

//菱形继承 虚继承关键字（virtual）
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
	//没有虚拟继承时，b中有_a,c中也有_a
	d.B::_a = 1;
	d.C::_a = 2;
	d._b = 3;
	d._c = 4;
	d._d = 5;
	return 0;
}


























