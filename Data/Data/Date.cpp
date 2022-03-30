#include<iostream>
#include "Date.h"
using namespace std;
// ��ȡĳ��ĳ�µ�����
int Date::GetMonthDay(int year, int month)
{
	//�ȶ���һ������洢������12�·ݵ��������ڵ����ж��Ƿ�Ϊ����
	static int monthdayarray[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};//���鲻��ı䣬���Զ���ɾ�̬
	int day = monthdayarray[month];
	if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
	{
		day += 1;//ֻ���Ƕ�����������·ݲ���Ҫ�ж��Ƿ�Ϊ����,�����жϿ�����ǰ
	}
	return day;
}
//��ӡ������
void Date::Print()
{
	//���ܹ��ӡ�����ж�һ�������Ƿ����
	if (_month <= 12)//�����·�С�ڣ�����12
	{
		//��ξ��ǻ�ȡ����,���бȽ�
		int monthday = GetMonthDay(_year, _month);
		if (_day <= monthday)
			cout << _year << '-' << _month << '-' << _day << endl;
		else
		{
			cout << "�����������->";
			cout << _year << '-' << _month << '-' << _day << endl;
		}
	}
	else
	{
		cout << "�����������->";
		cout << _year << '-' << _month << '-' << _day << endl;
	}
}
// ȫȱʡ�Ĺ��캯��
Date::Date(int year, int month, int day)
{
	_year = year;
	_month = month;
	_day = day;
}
Date::~Date()//������Ļ�Ĭ�����ɵľ͹���
{

}
// �������캯��
Date::Date(const Date& d)
{
	_year=d._year;
	_month = d._month;
	_day = d._day;
}
// ��ֵ���������
Date& Date::operator= (const Date& d)//*this�ڽ���Ҳ�������٣����Կ��Դ�����
{
	_year=d._year;
	_month = d._month;
	_day = d._day;
	return *this;
}
// ����+=����
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
	////Ҫ���˾ͽ��������������˽��ֱ꣬������С�ڸ��·ݵ�����
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
// ����+����
Date Date::operator+(int day)
{
	//��Ϊ�Ӳ���ı�ԭ�������ڣ����Ծ����Ƕ���һ���µ������洢�Ӻ������
	//��Ϊ�Ǿֲ��������Խ���ʱ�����٣��ô�ֵ����
	Date ret(*this);//��������һ����
	ret += day;
	return ret;
}
//����-=����
Date& Date::operator-=(int day)
{
	//��������Ǹ���������
	if (day < 0)
	{
		return *this += (-day);
	}
	//���ȵĻ���Ҫ�����������������½�λ���������������λ
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
// ����-����
Date Date::operator-(int day)//ԭ��ͬ+
{
	Date ret(*this);//��������һ����
	ret -= day;
	return ret;
}
// ǰ��++(�����ı�)
//�Զ���������û�����ǰ�ñȽϺã�����++��Ҫ������������
Date& Date::operator++()
{
	*this += 1;
	return *this;
}
//����++
Date Date::operator++(int)
{
	Date ret = *this;//��������
	*this += 1;
	return ret;//����ʱ�´������
}
//ǰ��--
Date& Date::operator--()
{
	*this -= 1;
	return *this;
}
//����--
Date Date::operator--(int)
{
	Date ret = *this;
	*this -= 1;
	return ret;
}
// >���������
bool Date::operator>(const Date& d)
{
	if ((_year > d._year) ||
		(_year == d._year && _month > d._month) ||
		(_year == d._year && _month == d._month && _day > d._day))
		return true;
	else
		return false;
}
// ==���������
bool Date::operator==(const Date& d)
{
	return (_year == d._year) && (_month == d._month) && (_day == d._day);
}
// >=���������
bool Date::operator>=(const Date& d)
{
	return (*this > d) || (*this == d);
}
// <���������
bool Date::operator<(const Date& d)
{
	return !(*this >= d);
}
// <=���������
bool Date::operator<=(const Date& d)
{
	return !(*this > d);
}
// !=���������
bool Date::operator!=(const Date& d)
{
	return !(*this == d);
}
// ����-���� ��������
int Date::operator-(const Date& d)
{
	Date max = *this;
	Date min = d;
	int flag = 1;//Ĭ�ϵ�һ�����ڴ��ڵڶ�������
	if (*this < d)//����ڶ������ڴ�
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
	Date start(1900,1,1);//��ʼ��������һ
	int count = *this - start;
	const char* dayarr[7] = { "����һ","���ڶ�","������","������","������","������","������"};
	cout << dayarr[count % 7] << endl;
}