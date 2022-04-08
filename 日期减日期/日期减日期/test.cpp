#include<iostream>
using namespace std;
class Date
{
public:
	Date(int year, int month, int day)
		:_year(year)
		, _month(month)
		, _day(day)
	{}
	int GetMonthDay(int year, int month)
	{
		static int monthdayarray[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
		int day = monthdayarray[month];
		if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
		{
			day += 1;
		}
		return day;
	}
	Date& operator++()
	{
		_day += 1;
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
	}
	bool operator<(const Date& d)
	{
		if ((_year < d._year) ||
			(_year == d._year && _month < d._month) ||
			(_year == d._year && _month == d._month && _day < d._day))
			return true;
		else
			return false;
	}
	bool operator!=(const Date& d)
	{
		return !((_year == d._year) && (_month == d._month) && (_day == d._day));
	}
	int operator-(const Date& d)
	{
		Date max = *this;
		Date min = d;
		if (*this < d)
		{
			max = d;
			min = *this;
		}
		int count = 1;
		while (min != max)
		{
			++min;
			++count;
		}
		return count ;
	}
private:
	int _year;
	int _month;
	int _day;
};
int main()
{
	int d1, d2;
	while (cin >> d1 >> d2)
	{
		int year1, month1, day1, year2, month2, day2;
		year1 = d1 / 10000;
		month1 = d1 / 100 % 100;
		day1 = d1 % 100;
		year2 = d2 / 10000;
		month2 = d2 / 100 % 100;
		day2 = d2 % 100;
		Date dd1(year1, month1, day1);
		Date dd2(year2, month2, day2);
		cout << dd1-dd2 << endl;
	}
	return 0;
}