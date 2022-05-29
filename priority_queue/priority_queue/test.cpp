#include<iostream>
#include<queue>
#include<vector>
#include<functional>
using namespace std;
namespace yyr
{
	class Date
	{
	public:
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
		void Print()
		{
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
		Date(int year, int month, int day)
		{
			_year = year;
			_month = month;
			_day = day;
		}
		~Date()
		{

		}
		Date(const Date& d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}
		// 赋值运算符重载
		Date& operator= (const Date& d)//*this在结束也不会销毁，所以可以传引用
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
			return *this;
		}
		// 日期+=天数
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
		// 日期+天数
		Date operator+(int day)
		{
			Date ret(*this);
			ret += day;
			return ret;
		}
		//日期-=天数
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
		// 日期-天数
		Date operator-(int day)//原理同+
		{
			Date ret(*this);//拷贝构造一个类
			ret -= day;
			return ret;
		}
		Date& operator++()
		{
			*this += 1;
			return *this;
		}
		//后置++
		Date operator++(int)
		{
			Date ret = *this;//拷贝构造
			*this += 1;
			return ret;//返回时会拷贝构造
		}
		//前置--
		Date& operator--()
		{
			*this -= 1;
			return *this;
		}
		//后置--
		Date operator--(int)
		{
			Date ret = *this;
			*this -= 1;
			return ret;
		}
		// >运算符重载
		bool operator>(const Date& d) const
		{
			if ((_year > d._year) ||
				(_year == d._year && _month > d._month) ||
				(_year == d._year && _month == d._month && _day > d._day))
				return true;
			else
				return false;
		}
		// ==运算符重载
		bool operator==(const Date& d) const
		{
			return (_year == d._year) && (_month == d._month) && (_day == d._day);
		}
		// >=运算符重载
		bool operator>=(const Date& d) const
		{
			return (*this > d) || (*this == d);
		}
		// <运算符重载
		bool operator<(const Date& d) const
		{
			return !(*this >= d);
		}
		// <=运算符重载
		bool operator<=(const Date& d) const
		{
			return !(*this > d);
		}
		// !=运算符重载
		bool operator!=(const Date& d)
		{
			return !(*this == d);
		}
		// 日期-日期 返回天数
		int operator-(const Date& d)
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
		void GetWeekday()
		{
			Date start(1900, 1, 1);//起始日期星期一
			int count = *this - start;
			const char* dayarr[7] = { "星期一","星期二","星期三","星期四","星期五","星期六","星期日" };
			cout << dayarr[count % 7] << endl;
		}
		private:
			int _year;
			int _month;
			int _day;
	};

	template<class T>
	struct less
	{
		bool operator()(const T& x, const T& y) const
		{
			return x < y;
		}
	};
	template<class T>
	struct greater
	{
		bool operator()(const T& x, const T& y) const
		{
			return x > y;
		}
	};
}
void fun1()
{
	//priority_queue<int> pq;
	//priority_queue<int,vector<int>,greater<int>> pq;
	vector<int> pq;
	pq.push_back(3);
	pq.push_back(4);
	pq.push_back(7);
	pq.push_back(2);
	pq.push_back(1);
	//sort(pq.begin(), pq.end());
	sort(pq.begin(), pq.end(),greater<int>());//从大到小
	//在上面的优先级队列中加的是greater<int> ---->因为那是一个模板参数，传的是类型
	//而sort是一个函数，里面传的是对象，这里用了一个匿名对象
	//如果数据类型不支持比较，或者比较的方式不是自己想要的那么就需要自己实现一个仿函数
	for (auto e : pq)
	{
		cout << e << " ";
	}
	/*while (!pq.empty())
	{
		cout << pq.top() << " ";
		pq.pop();
	}*/

}
void fun2()
{
	yyr::less<int> ls;
	cout << ls(1, 2) << endl;
	yyr::greater<int> gt;
	//下面两个是一个含义
	//像less/greater就是仿函数，而ls/gt就是函数对象
	cout << gt.operator()(4, 3) << endl;
	cout << gt(4, 5) << endl;
}
//-------------------------------------------------------------------------------------------------------------------------
//模板进阶
//非类型模板参数--规定必须是整型常量
template<class T,size_t N=100>
struct Stack
{
	//如果就是想定义一个静态栈，就可以采用这种方法
private:
	T _st[N];
	size_t _top;
};
//函数模板的特化
//这个就是正常的函数模板匹配
template <class T>
bool Objless(T d1 , T d2) //1
{
	return d1 < d2;
}
bool Objless( yyr::Date*& p1, yyr::Date*& p2) //2
{
	return *p1 < *p2;
}


//这种方法就是函数模板的特化
template<>
bool Objless<yyr::Date*>(yyr::Date* p1, yyr::Date* p2)//3
{
	return *p1 < *p2;
}
//函数模板的特化比较鸡肋，在实际应用中完全可以重载一个Date* 的函数，2和3可以同时存在，并且编译器会自动调用2
void fun3()
{
	//在使用过程中难免会遇到这样的问题，以日期类来举例子
	cout << Objless(1, 2) << endl;//这是没有问题的
	yyr::Date* d1 = new yyr::Date(2022, 3, 20);
	yyr::Date* d2 = new yyr::Date(2022, 5, 30);
	cout << Objless(d1, d2) << endl;//如果没有2，运行出来是有问题的，他比较的是指针
}

template<class T>
struct Less
{
	bool operator()(const T& x, const T& y)
	{
		return x < y;
	}
};
template<>
struct Less<yyr::Date*>
{
	bool operator()(yyr::Date*& d1,yyr::Date*& d2)
	{
		return *d1 < *d2;
	}
};
void fun4()
{
	yyr::Date* d1 = new yyr::Date(2022, 3, 20);
	yyr::Date* d2 = new yyr::Date(2022, 5, 30);
	cout<<Less<yyr::Date*>()(d1,d2);
	//cout << ls(d1, d2);
}
//int main()
//{
//	fun4();
//	//fun3();
//}