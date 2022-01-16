#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string.h>
using namespace std;
//int& Add(int x, int y)
//{
//	int c = x + y;
//	return c;
//}
//int main()
//{
//	int& ret = Add(1, 2);
//	Add(8,9);
//	cout << ret << endl;
//}
struct Student
{
	//成员函数存在公共区，当调用的时候会有一个隐藏this指针
	//对象的大小是由类的成员变量来决定的
public:
	//void fun(Student* this,int age, const char name[], const char id[])
	//既然是隐藏的this，所以他不能出现在声明和定义当中，但是他可以出现在成员函数的内部
	//Student()//重载函数
	//{
	//    //在对象创建时自动调用，有三种形式，系统默认生成的构造函数什么都不会做，只会调用自定义变量类型的构造函数
	//}
	Student(int age = 10, const char name[] = "默认", const char id[] = "默认")
	{
		//_age = age;
		this->_age = age;//这样同样能运行
		//strcpy(_name,name);
		strcpy(this->_name, name);//同理
		strcpy(_id, id);
	}
	~Student()//析构函数
	{
	//在对象出作用域时自动调用，没有会自动生成，但是不会有任何作用
	}
	void fun(int age=10, const char name[]="默认", const char id[]="默认")
	{
		//_age = age;
		this->_age = age;//这样同样能运行
		//strcpy(_name,name);
		strcpy(this->_name, name);//同理
		strcpy(_id,id);
	}
	//void print(Student* this)
	void print()
	{
		cout << _age << "   " << _name << "   " << _id << endl;
	}
	//最好不要用默认的缺省值，最好自己写
private:
	int _age;
	char _name[20];
	char _id[20];
};
int main()
{
	//s1就是类Student创建的对象，不需要加上struct，且因为要兼容c，所以struct默认的访问限制符为public
	Student s1;
	//使用成员函数
	//想一个问题，函数存储在公共区，那么他是怎么区分不同的对象调用的函数呢？
	//这就引出了隐藏的this指针
	//实际的调用是这样的
	//fun(&s1,18,"小明","340406220");
	s1.fun(18,"小明","340406220");
	//print(&s1);
	s1.print();
	//C++中还将auto的用法改变了，auto在c++中变成了一个可自动推导类型的一个关键字
	//只是auto推导的关键字会忽略const属性,且auto定义的变量必须初始化
	//auto x;错误
	//auto s2 = s1;
	//Student s3;
	//auto s4 = s3;
	//cout << typeid(s1).name() << endl;
	//cout << typeid(s2).name()<<endl;//这个是输出变量类型
	//cout << typeid(s3).name() << endl;
	//cout << typeid(s4).name() << endl;
}