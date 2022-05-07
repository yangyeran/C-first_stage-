@[TOC](目录)

补：

* 迭代器是一个左闭右开区间

* 函数模板的模板参数要传迭代器区间时，是有命名规范的
  * 迭代器分类：input_iterator(只读迭代器)、output_iterator(只写迭代器)、forwad_iterator(单向迭代器)、bidirectional_iterator(双向迭代器)、randomaccess_iterator(随机迭代器)

## vector

简单理解vector是表示可变大小数组的序列容器

### vector常用接口的使用

#### 一、vector的定义

|                      构造函数声明                      |         接口说明         | 序列 |
| :----------------------------------------------------: | :----------------------: | :--: |
|                        vector()                        |        无参的构造        |  1   |
| vector(size_type n,const value_type& val=value_type()) |    构造并初始化n个val    |  2   |
|                vector(const vector& x)                 |         拷贝构造         |  3   |
|   vector (InputIterator first, InputIterator last);    | 使用迭代器进行初始话构造 |  4   |

```c++
	//1
	vector<int> arr1;
	//3
	vector<int> arr3(arr2);
	//2
	vector<int> arr4(5,0);
	//4 这个是用迭代器实现的
	string std("hello");
	vector<char> ch1(std.begin(), std.end());
	//5 还可以这样初始化只不过C++98不支持这样
	vector<int> arr2 = { 1,2,3,4,5 };
```

#### 二、vector iterator 的使用  

| iterator的使用  | 接口说明                                                     |
| --------------- | ------------------------------------------------------------ |
| begin()+end()   | 获取第一个数据位置的iterator/const_iterator， 获取最后一个数据的下一个位置 的iterator/const_iterator |
| rbegin()+rend() | 获取最后一个数据位置的reverse_iterator，获取第一个数据前一个位置的 reverse_iterator |

```c++
	//接着上面定义的ch1和arr3   
	//不不想写这么长也可以用auto自动推导
	//for (auto it = ch1.begin(); it != ch1.end(); ++it)
	for (vector<char>::iterator it = ch1.begin(); it != ch1.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
	//for (auto it = arr3.rbegin(); it != arr3.rend(); ++it)
	for (vector<int>::reverse_iterator it = arr3.rbegin(); it != arr3.rend(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
```

#### 三、vector空间增长

| 容量空间 | 接口说明               |
| -------- | ---------------------- |
| size     | 获取数据个数           |
| capacity | 获取容量大小           |
| empty    | 判断是否为空           |
| resize   | 改变vector的size       |
| reserve  | 改变vector放入capacity |

<img src="C:/Users/yangyr0206/AppData/Roaming/Typora/typora-user-images/image-20220421203408301.png" alt="image-20220421203408301"  />

![image-20220421203959677](C:/Users/yangyr0206/AppData/Roaming/Typora/typora-user-images/image-20220421203959677.png)

* capacity的代码在vs和g++的增长是不一样的，vs下capacity是按1.5倍增长的，g++是按2倍增长的(vs是PJ版本的STL，g++是SGI版本的STL)
* reserve只负责开辟空间，如果确定知道需要多少空间，reserve可以缓解vector增容的代价缺陷问题
* resize在开空间的同时还会进行初始化，会影响size

* resize如果出现size比原先的小的情况，虽然不会缩小空间但是会改变size

  ![image-20220421205137786](C:/Users/yangyr0206/AppData/Roaming/Typora/typora-user-images/image-20220421205137786.png)

#### 四、vector 增删查改  

| vector增删查改 | 接口说明                                                     |
| -------------- | ------------------------------------------------------------ |
| push_back      | 尾插                                                         |
| pop_back       | 尾删                                                         |
| find           | 查找(这个是算法模块实现的，不是vector的成员接口)             |
| insert         | 在position之前插入val                                        |
| erase          | 删除posistion位置的数据                                      |
| swap           | 交换两个vector的数据空间                                     |
| operator[]     | 像数组一样访问                                               |
| clear          | 清空数据，不会清除空间                                       |
| assign         | 新内容是从‎‎第一个‎‎和‎‎最后‎一个之间的范围内的每个元素构造的元素，顺序相同；新内容是n 个‎‎元素，每个元素都初始化为val‎的副本。‎‎如果发生重新分配，则使用‎[‎内部分配器分配‎](http://www.cplusplus.com/vector::get_allocator)‎所需的存储。 |

```c++
	vector<int>arr1;
	//尾插一个数据
	arr1.push_back(1);
	arr1.push_back(2);
	arr1.push_back(3);
	arr1.push_back(4);
	arr1.push_back(5);
	//用迭代器去遍历
	for (vector<int>::iterator it = arr1.begin(); it != arr1.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
	//左边传的是迭代器，右边是要插入的数据
	arr1.insert(arr1.begin() + 3, 6);
	arr1.insert(arr1.begin() + 3, 7);
	for (vector<int>::iterator it = arr1.begin(); it != arr1.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
	//尾删一个数据，没有参数直接调用即可
	arr1.pop_back();
	arr1.pop_back();
	for (vector<int>::iterator it = arr1.begin(); it != arr1.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
	//迭代器传位置
	arr1.erase(arr1.end()-2);
	for (vector<int>::iterator it = arr1.begin(); it != arr1.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
	vector<int> arr2;
	//交换
	swap(arr1, arr2);
	swap(arr2[0], arr2[3]);

	for (vector<int>::iterator it = arr1.begin(); it != arr1.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
	for (vector<int>::iterator it = arr2.begin(); it != arr2.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
	arr1 = { 9,8,7,6,5 };
	for (vector<int>::iterator it = arr1.begin(); it != arr1.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
	//清空数据
	arr1.clear();
	for (vector<int>::iterator it = arr1.begin(); it != arr1.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
```

![image-20220421215143725](C:/Users/yangyr0206/AppData/Roaming/Typora/typora-user-images/image-20220421215143725.png)

```c++
	vector<int>arr1 = { 9,8,7,6,5 };
	vector<int>arr2 = { 0,1,2,3,4,10,11,12 };
	//通过迭代器，可以给arr1赋值其他对象的数据
	//如果赋值的那个对象比原先对象要打大，会自动扩容至与大的对象的capacity相同
	arr1.assign(arr2.begin(), arr2.end());
	for (vector<int>::iterator it = arr1.begin(); it != arr1.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
	//左边是个数，右边是值，也是就赋8个0
	arr1.assign(8, 0);
	for (vector<int>::iterator it = arr1.begin(); it != arr1.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
```

```c++
	//find不是vector的成员接口，是算法库里面的，使用时必须包含头文件 #include<algorithm>
	vector<int>arr1 = { 1,2,3,4,5,6,7,8 };
	//find前两个参数传的是一段迭代器的区间，第三个参数是需要查找的数据
	//如果能找到就返回找到数据位置的迭代器，如果找不到就返回end()，所以要进行判断
	vector<int>::iterator it=find(arr1.begin(), arr1.end(),9);
	if (it != arr1.end())
	{
		cout << *it << endl;
	}
```
### vector的一些用法

我们有时候做题时会用到两层vector嵌套使用例如：

```c++
vector<vector<int>>//其实就是一个可变的二维数组
vector<vector<string>>//.....
```

这里用一个力扣上面的[杨辉三角](https://leetcode-cn.com/problems/pascals-triangle/description/)来举例：

```c++
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> ret;
        //这里不能用reserve，因为reserve只是扩容，不会初始化，后续给里面空间扩容会出问题
        ret.resize(numRows);//这里就相当于开了5个类型为vector<int>的数组
        for (size_t i = 0; i < numRows; ++i)
        {
            //开的就是类型为int的数组
            ret[i].resize(i+1, 0);
            ret[i][0] = 1;
            ret[i][i] = 1;
        }
        for (size_t i = 0; i < numRows; ++i)
        {
            for (size_t j = 0; j <= i; ++j)
            {
                if (ret[i][j] == 0)
                {
                    ret[i][j] = ret[i - 1][j] + ret[i - 1][j - 1];
                }
            }
        }
        return ret;
    }
};
```

