#include<iostream>
using namespace std;
class Bass
{
public:
	Bass(int j)
		:i(j)
	{}
	virtual ~Bass() {};
	void func1()
	{
		i *= 10;
		func2();
	}
	int getValue()
	{
		return i;
	}
protected:
	int i;
	virtual void  func2()
	{
		i++;
	}
};
class Child :public Bass
{
public:
	Child(int j)
		:Bass(j)
	{}
	void func1()
	{
		i *= 100;
		func2();
	}
protected:
	void func2()
	{
		i += 2;
	}
};
int main()
{
	Bass* pb = new Child(1);
	//切片之后是父类的指针就会调用父类的成员函数，只有构成了多态的虚函数才会去调用子类的虚函数
	pb->func1();
	cout << pb->getValue() << endl;
	delete pb;
}

////计算日期到天的转换
#include<iostream>
using namespace std;
//首先判断是否为润年，定义一个数组来存储月份
int main()
{
	int year, month, day;
	int ret = 0;
	cin >> year >> month >> day;
	int months[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
	{
		months[2] = 29;
	}
	for (int i = 0; i < month; ++i)
	{
		ret += months[i];
	}
	ret += day;
	cout << ret << endl;
	return 0;
}

//幸运的袋子
/*这道题的本质是在集合中找出符合条件的子集。
  对于两个任意正整数a，b来说，如果a+b<ab，则必须有一个数为1，可以用数论来证明，这里不再赘述。
  推广到任意k个正整数，假设a1,a2,…ak，如果不满足条件，即sum<=multi，如果再选一个数使sum+b > multib，这个b一定是1，相反，如果选择的b>1，则sum+b < multi*b，那么a1,a2,…ak,b就不满足给定的条件。
  所以要将这些球进行升序排序。每次从小到大选择，当选择到a1,a2,…ak-1时满足给定条件，再增加ak是不满足条件，那么ak必然要大于等于之前的最大值，如果继续向后选择更大的数，必然无法满足给定条件。
  如果有多个1，并且k=1使不满足条件，但是下一个元素仍为1，就可以满足条件，所以当位置吐过是1，虽然不满足条件，但是应该继续向后搜索，因为仍然有可能满足条件。
对于重复的数字，组合只能算一个，所以要跳过这个数字，也就是去重*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int  getLuckBox(vector<int> x, size_t n, size_t pos, int sum, int multi)
{
	int count = 0;
	for (size_t i = pos; i < n; ++i)
	{
		sum += x[i];
		multi *= x[i];
		if (sum > multi)
		{
			//如果当前位置可以满足要求，就继续从下一个位置开始
			count += 1 + getLuckBox(x, n, i + 1, sum, multi);
		}
		else if (x[i] == 1)
		{
			//如果这个位置是1并且不满足，可以从下一个位置尝试
			count += getLuckBox(x, n, i + 1, sum, multi);
		}
		else
		{
			//如果当前位置不满足，那么之后更大的数字也不可能满足，直接直接返回，不再查找
			break;
		}
		//在搜索下一个位置前，要先恢复sum和multi
		sum -= x[i];
		multi /= x[i];
		//如果喝下一个位置一样，就直接跳过，不能有重复
		while (i < n - 1 && x[i] == x[i + 1])
		{
			++i;
		}
	}
	return count;
}
int main()
{
	size_t n;
	while (cin >> n)
	{
		vector<int> x;
		for (size_t i = 0; i < n; ++i)
		{
			int tmp;
			cin >> tmp;
			x.push_back(tmp);
		}
		//按升序排序
		sort(x.begin(), x.end());
		cout << getLuckBox(x, n, 0, 0, 1);
	}
	return 0;
}
