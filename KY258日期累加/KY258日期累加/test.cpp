#include<iostream>
using namespace std;
class Date
{
public:
    Date(int year = 1, int month = 1, int day = 1)
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
    Date& operator+=(int day)
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
    }
    Date& operator-=(int day)
    {
        if (day < 0)
        {
            return *this += (-day);
        }
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
    void Printf() const
    {
        if (_month < 10)
        {
            if (_day > 10)
                cout << _year << "-0" << _month << "-" << _day << endl;
            else
                cout << _year << "-0" << _month << "-0" << _day << endl;
        }
        else
        {
            if (_day > 10)
                cout << _year << "-" << _month << "-" << _day << endl;
            else
                cout << _year << "-" << _month << "-0" << _day << endl;
        }
    }
    ~Date()
    {

    }
private:
    int _year;
    int _month;
    int _day;
};
int main()
{
    int i = 0;
    cin >> i;
    for (int j = 0; j < i; j++)
    {
        int y, m, d, n;
        cin >> y >> m >> d >> n;
        Date d1(y, m, d);
        d1 += n;
        d1.Printf();
    }
    return 0;
}