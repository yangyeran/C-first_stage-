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
	//��Ա�������ڹ������������õ�ʱ�����һ������thisָ��
	//����Ĵ�С������ĳ�Ա������������
public:
	//void fun(Student* this,int age, const char name[], const char id[])
	//��Ȼ�����ص�this�����������ܳ����������Ͷ��嵱�У����������Գ����ڳ�Ա�������ڲ�
	//Student()//���غ���
	//{
	//    //�ڶ��󴴽�ʱ�Զ����ã���������ʽ��ϵͳĬ�����ɵĹ��캯��ʲô����������ֻ������Զ���������͵Ĺ��캯��
	//}
	Student(int age = 10, const char name[] = "Ĭ��", const char id[] = "Ĭ��")
	{
		//_age = age;
		this->_age = age;//����ͬ��������
		//strcpy(_name,name);
		strcpy(this->_name, name);//ͬ��
		strcpy(_id, id);
	}
	~Student()//��������
	{
	//�ڶ����������ʱ�Զ����ã�û�л��Զ����ɣ����ǲ������κ�����
	}
	void fun(int age=10, const char name[]="Ĭ��", const char id[]="Ĭ��")
	{
		//_age = age;
		this->_age = age;//����ͬ��������
		//strcpy(_name,name);
		strcpy(this->_name, name);//ͬ��
		strcpy(_id,id);
	}
	//void print(Student* this)
	void print()
	{
		cout << _age << "   " << _name << "   " << _id << endl;
	}
	//��ò�Ҫ��Ĭ�ϵ�ȱʡֵ������Լ�д
private:
	int _age;
	char _name[20];
	char _id[20];
};
int main()
{
	//s1������Student�����Ķ��󣬲���Ҫ����struct������ΪҪ����c������structĬ�ϵķ������Ʒ�Ϊpublic
	Student s1;
	//ʹ�ó�Ա����
	//��һ�����⣬�����洢�ڹ���������ô������ô���ֲ�ͬ�Ķ�����õĺ����أ�
	//������������ص�thisָ��
	//ʵ�ʵĵ�����������
	//fun(&s1,18,"С��","340406220");
	s1.fun(18,"С��","340406220");
	//print(&s1);
	s1.print();
	//C++�л���auto���÷��ı��ˣ�auto��c++�б����һ�����Զ��Ƶ����͵�һ���ؼ���
	//ֻ��auto�Ƶ��Ĺؼ��ֻ����const����,��auto����ı��������ʼ��
	//auto x;����
	//auto s2 = s1;
	//Student s3;
	//auto s4 = s3;
	//cout << typeid(s1).name() << endl;
	//cout << typeid(s2).name()<<endl;//����������������
	//cout << typeid(s3).name() << endl;
	//cout << typeid(s4).name() << endl;
}