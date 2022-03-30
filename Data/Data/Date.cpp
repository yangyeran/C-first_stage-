#include<iostream>
#include "Date.h"
using namespace std;
// 获取某年某月的天数
int Date::GetMonthDay(int year, int month)
{
	//先定义一个数组存储常见的12月份的天数，在单独判断是否为闰年
	static int monthdayarray[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};//数组不会改变，可以定义成静态
	int day = monthdayarray[month];
	if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
	{
		day += 1;//只有是二月这个特殊月份才需要判断是否为闰年,所以判断可以提前
	}
	return day;
}
//打印年月日
void Date::Print()
{
	//不能光打印还得判断一下日期是否合理
	if (_month <= 12)//首先月份小于，等于12
	{
		//其次就是获取日期,进行比较
		int monthday = GetMonthDay(_year, _month);
		if (_day <= monthday)
			cout << _year << '-' << _month << '-' << _day << endl;
		else
		{
			cout << "日期输入错误->";
			cout << _year << '-' << _month << '-' << _day << endl;
		}
	}
	else
	{
		cout << "日期输入错误->";
		cout << _year << '-' << _month << '-' << _day << endl;
	}
}
// 全缺省的构造函数
Date::Date(int year, int month, int day)
{
	_year = year;
	_month = month;
	_day = day;
}
Date::~Date()//日期类的话默认生成的就够了
{

}
// 拷贝构造函数
Date::Date(const Date& d)
{
	_year=d._year;
	_month = d._month;
	_day = d._day;
}
// 赋值运算符重载
Date& Date::operator= (const Date& d)//*this在结束也不会销毁，所以可以传引用
{
	_year=d._year;
	_month = d._month;
	_day = d._day;
	return *this;
}
// 日期+=天数
Date& Date::operator+=(int day)
{
	if (day < 0)
	{
		return *this -= (-day);
	}
	_day += day;
	while (_day > GetMonthDay(_year, _month))
	{
		_day -= GetMonthDay(_year, _month);
		++_month;
		if (_month == 13)
		{
			_year++;
			_month = 1;
		}
	}
	return *this;
	////要满了就进月数，月数满了进年，直到天数小于该月份的天数
	//int totalday = day + _day;
	//while (totalday >= GetMonthDay(_year, _month))
	//{
	//	if (_month <= 12)
	//	{
	//		totalday -= GetMonthDay(_year,_month);
	//		_month++;
	//	}
	//	else
	//	{
	//		_year++;
	//		_month = 1;
	//	}
	//}
	//_day = totalday;
	//return *this;
}
// 日期+天数
Date Date::operator+(int day)
{
	//因为加不会改变原来的日期，所以就是是定义一个新的类来存储加后的日期
	//因为是局部变量所以结束时会销毁，用传值返回
	Date ret(*this);//拷贝构造一个类
	ret += day;
	return ret;
}
//日期-=天数
Date& Date::operator-=(int day)
{
	//如果减的是负数的天数
	if (day < 0)
	{
		return *this += (-day);
	}
	//减等的话就要考虑天数不够就向月借位，月数不够向年借位
	_day -= day;
	while (_day <= 0)
	{
		--_month;
		if (_month == 0)
		{
			--_year;
			_month = 12;
		}
		_day += GetMonthDay(_year, _month);
	}
	return *this;
}
// 日期-天数
Date Date::operator-(int day)//原理同+
{
	Date ret(*this);//拷贝构造一个类
	ret -= day;
	return ret;
}
// 前置++(不做改变)
//自定义类型最好还是用前置比较好，后置++需要拷贝构造两次
Date& Date::operator++()
{
	*this += 1;
	return *this;
}
//后置++
Date Date::operator++(int)
{
	Date ret = *this;//拷贝构造
	*this += 1;
	return ret;//返回时会拷贝构造
}
//前置--
Date& Date::operator--()
{
	*this -= 1;
	return *this;
}
//后置--
Date Date::operator--(int)
{
	Date ret = *this;
	*this -= 1;
	return ret;
}
// >运算符重载
bool Date::operator>(const Date& d)
{
	if ((_year > d._year) ||
		(_year == d._year && _month > d._month) ||
		(_year == d._year && _month == d._month && _day > d._day))
		return true;
	else
		return false;
}
// ==运算符重载
bool Date::operator==(const Date& d)
{
	return (_year == d._year) && (_month == d._month) && (_day == d._day);
}
// >=运算符重载
bool Date::operator>=(const Date& d)
{
	return (*this > d) || (*this == d);
}
// <运算符重载
bool Date::operator<(const Date& d)
{
	return !(*this >= d);
}
// <=运算符重载
bool Date::operator<=(const Date& d)
{
	return !(*this > d);
}
// !=运算符重载
bool Date::operator!=(const Date& d)
{
	return !(*this == d);
}
// 日期-日期 返回天数
int Date::operator-(const Date& d)
{
	Date max = *this;
	Date min = d;
	int flag = 1;//默认第一个日期大于第二个日期
	if (*this < d)//如果第二个日期大
	{
		max = d;
		min = *this;
		flag = -1;
	}
	int count = 0;
	while (min != max)
	{
		++min;
		++count;
	}
	return count * flag;
}
void Date::GetWeekday()
{
	Date start(1900,1,1);//起始日期星期一
	int count = *this - start;
	const char* dayarr[7] = { "星期一","星期二","星期三","星期四","星期五","星期六","星期日"};
	cout << dayarr[count % 7] << endl;
}