#pragma once
class Date
{
public:
	// ��ȡĳ��ĳ�µ�����
	int GetMonthDay(int year, int month);
	//���ڼ�
	void GetWeekday();
	//��ӡ������
	void Print();
	// ȫȱʡ�Ĺ��캯��
	Date(int year = 1, int month = 1, int day = 1);
	// �������캯��
  // d2(d1)
	Date(const Date& d);
	// ��ֵ���������
  // d2 = d3 -> d2.operator=(&d2, d3)
	Date& operator=(const Date& d);
	// ��������
	~Date();
	// ����+=����
	Date& operator+=(int day);
	// ����+����
	Date operator+(int day);
	// ����-����
	Date operator-(int day);
	// ����-=����
	Date& operator-=(int day);
	// ǰ��++(�����ı�)
	Date& operator++();
	// ����++���ඨ��һ��int�Ͳ�����ûʵ�����ã�ֻ��Ϊ�˷������أ�
	Date operator++(int);
	// ǰ��--
	Date& operator--();
	// ����--
	Date operator--(int);
	// >���������
	bool operator>(const Date& d);
	// ==���������
	bool operator==(const Date& d);
	// >=���������
	bool operator>=(const Date& d);
	// <���������
	bool operator<(const Date& d);
	// <=���������
	bool operator<=(const Date& d);
	// !=���������
	bool operator!=(const Date& d);
	// ����-���� ��������
	int operator-(const Date& d);
private:
	int _year;
	int _month;
	int _day;
};
