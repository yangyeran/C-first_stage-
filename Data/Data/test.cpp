#include <iostream>
#include "Date.h"
using namespace std;
void test1()//��鹹�캯���ʹ�ӡ�����Ϳ�������
{
	Date d1;
	Date d2(2013, 2, 29);
	Date d3(2020, 2, 29);
	Date d4(2020, 3, 32);
	Date d5(d1);
	d1.Print();
	d2.Print();
	d3.Print();
	d4.Print();
	d5.Print();
}
void test2()//���������
{
	Date d3(2020, 2, 29);
	Date d4=d3;
	//Date d5 = ++d4;
	Date d5 = d4++;
	d3.Print();
	d4.Print();
	d5.Print();
	//d3 -= 29;
	/*d3 -= 100;
	d3.Print();*/
	//d3.Print();
	//Date d1(2022, 1, 17);
	//Date d2 = d3 + 100;
	//d2.Print();
	//d3 += 100;
	//d3.Print();
	//d3 += 2000;
	//d3.Print();
	/*Date d4;
	d4.Print();*/
	//d4 = d3;
	//d4.Print();
}
//void test3()
//{
//	Date d3(2020, 2, 29);
//	Date d4(2022,1,19);
//	int ret=(d3 >= d4);
//	/*int ret = (d4 >= d3);*/
//	cout << ret << endl;
//}
void test3()
{
	Date d4(2022, 1, 19);
	d4 -= 30;
	d4.Print();
}
int main()
{
	test1();
	//test2();
	//test3();
}
