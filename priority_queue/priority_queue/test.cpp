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
		// ��ֵ���������
		Date& operator= (const Date& d)//*this�ڽ���Ҳ�������٣����Կ��Դ�����
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
			return *this;
		}
		// ����+=����
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
		// ����+����
		Date operator+(int day)
		{
			Date ret(*this);
			ret += day;
			return ret;
		}
		//����-=����
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
		// ����-����
		Date operator-(int day)//ԭ��ͬ+
		{
			Date ret(*this);//��������һ����
			ret -= day;
			return ret;
		}
		Date& operator++()
		{
			*this += 1;
			return *this;
		}
		//����++
		Date operator++(int)
		{
			Date ret = *this;//��������
			*this += 1;
			return ret;//����ʱ�´������
		}
		//ǰ��--
		Date& operator--()
		{
			*this -= 1;
			return *this;
		}
		//����--
		Date operator--(int)
		{
			Date ret = *this;
			*this -= 1;
			return ret;
		}
		// >���������
		bool operator>(const Date& d) const
		{
			if ((_year > d._year) ||
				(_year == d._year && _month > d._month) ||
				(_year == d._year && _month == d._month && _day > d._day))
				return true;
			else
				return false;
		}
		// ==���������
		bool operator==(const Date& d) const
		{
			return (_year == d._year) && (_month == d._month) && (_day == d._day);
		}
		// >=���������
		bool operator>=(const Date& d) const
		{
			return (*this > d) || (*this == d);
		}
		// <���������
		bool operator<(const Date& d) const
		{
			return !(*this >= d);
		}
		// <=���������
		bool operator<=(const Date& d) const
		{
			return !(*this > d);
		}
		// !=���������
		bool operator!=(const Date& d)
		{
			return !(*this == d);
		}
		// ����-���� ��������
		int operator-(const Date& d)
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
		void GetWeekday()
		{
			Date start(1900, 1, 1);//��ʼ��������һ
			int count = *this - start;
			const char* dayarr[7] = { "����һ","���ڶ�","������","������","������","������","������" };
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
	sort(pq.begin(), pq.end(),greater<int>());//�Ӵ�С
	//����������ȼ������мӵ���greater<int> ---->��Ϊ����һ��ģ�����������������
	//��sort��һ�����������洫���Ƕ�����������һ����������
	//����������Ͳ�֧�ֱȽϣ����߱Ƚϵķ�ʽ�����Լ���Ҫ����ô����Ҫ�Լ�ʵ��һ���º���
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
	//����������һ������
	//��less/greater���Ƿº�������ls/gt���Ǻ�������
	cout << gt.operator()(4, 3) << endl;
	cout << gt(4, 5) << endl;
}
//-------------------------------------------------------------------------------------------------------------------------
//ģ�����
//������ģ�����--�涨���������ͳ���
template<class T,size_t N=100>
struct Stack
{
	//��������붨��һ����̬ջ���Ϳ��Բ������ַ���
private:
	T _st[N];
	size_t _top;
};
//����ģ����ػ�
//������������ĺ���ģ��ƥ��
template <class T>
bool Objless(T d1 , T d2) //1
{
	return d1 < d2;
}
bool Objless( yyr::Date*& p1, yyr::Date*& p2) //2
{
	return *p1 < *p2;
}


//���ַ������Ǻ���ģ����ػ�
template<>
bool Objless<yyr::Date*>(yyr::Date* p1, yyr::Date* p2)//3
{
	return *p1 < *p2;
}
//����ģ����ػ��Ƚϼ��ߣ���ʵ��Ӧ������ȫ��������һ��Date* �ĺ�����2��3����ͬʱ���ڣ����ұ��������Զ�����2
void fun3()
{
	//��ʹ�ù�����������������������⣬����������������
	cout << Objless(1, 2) << endl;//����û�������
	yyr::Date* d1 = new yyr::Date(2022, 3, 20);
	yyr::Date* d2 = new yyr::Date(2022, 5, 30);
	cout << Objless(d1, d2) << endl;//���û��2�����г�����������ģ����Ƚϵ���ָ��
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