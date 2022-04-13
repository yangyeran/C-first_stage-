@[toc](目录)

## String类

补：

* 编码：值和符号建立起映射关系--->形成编码表
  1. ASCII编码表---表示英文
  2. unicode--- 表示全世界文字编码表(utf-8 utf-16....)
  3. gbk---中国自己定做的编码表

* wchar_t 宽字符，一般是2个字节---->wstring

  <img src="C:/Users/yangyr0206/AppData/Roaming/Typora/typora-user-images/image-20220410221538628.png" alt="image-20220410221538628"  />
  
* getline() 获取一行字符

  ```c++
  	string s1;
  	getline(cin,s1);
  	//可以自己实现读取一行
  	string s2;
  	char ch = getchar();
  	while (ch != '\n')
  	{
  		s2 += ch;
  		ch = getchar();
  	}
  ```

---

### 初步了解string

1. string是表示字符串的字符串类

2. 该类的接口与常规容器的接口基本相同，再添加了一些专门用来操作string的常规操作。
   
3. string在底层实际是：basic_string模板类的别名，typedef basic_string<char, char_traits, allocator> string;
   
4. 不能操作多字节或者变长字符的序列。在**使用string类时，必须包含#include <string>以及using namespace std**;  

### string类的常用接口说明

#### string类对象的常见构造函数

| (constructor)函数名称   | 功能说明                         |
| ----------------------- | -------------------------------- |
| string()                | 构造空的string类对象，即空字符串 |
| string(const char* s)   | 用C-string来构造string类对象     |
| string(size_t n,char c) | string类对象中包含n个字符c       |
| string(const string& s) | 拷贝构造函数                     |

#### string类对象的容量操作  

| 函数名称              | 功能说明                                      |
| --------------------- | --------------------------------------------- |
| size(主)/length(了解) | 返回字符串有效字符长度                        |
| capacity              | 返回容量大小                                  |
| empty                 | 检测字符串释放为空串，是返回true，否返回false |
| clear(主)             | 清空有效字符                                  |
| reserve               | 为字符串预留空间                              |
| resize                | 将有效字符的个数改成n个，多出的空间用字符填充 |
| max_size(了解)        | 就是一个字符串最长能有多长                    |

**reserve和resize对比**

* reserve 只开空间，影响容量(只是扩容)
* resize 开空间，对这些空间给一个初始值，进行初始化(扩容加初始化)
* 都不会修改原先的数据

```c++
string st1("hello word");
//size和length的作用完全相同，建议最好使用size
//不包含最后作为结束标志的\0，是有效字符长度
cout<<st1.size()<<endl;
cout<<st1.length()<<endl;
cout<<st1.max_size<<endl;
//返回容量大小(会比总大小少1，因为'\0'不算在里面)
cout << st1.capacity() << endl;
//只会清空数据，不会释放空间
st1.clear();
//reserve用法就是
st1.reserve(num);//就是申请至少能存储num数据的空间
st2.resize(num);//或者可以给字符初始化 st2.resize(num,'c');
```

#### string类对象的访问及遍历操作  

| 函数名称    | 功能说明                                                     |
| ----------- | ------------------------------------------------------------ |
| oprator[]   | 返回pos位置的字符，const string类对象调用                    |
| begin+end   | begin获取第一个字符的迭代器+end获取最后一个字符下一个位置的迭代器 |
| rbegin+rend | rbegin指向的是最后一个有效字符位置，rend指向的的是第一个字符前面一个字符位置 |
| 范围for     | C++11支持更简洁的范围for的新遍历方式                         |

```c++
	string s1 = "hello word";
	//普通遍历
	for (size_t i = 0; i < s1.size(); ++i)
	{
		cout << s1[i] << " ";
	}
	cout<<endl;
	//迭代器方式遍历(正向)
	string::iterator it = s1.begin();
	//s1.begin()指向的是第一个元字符的地址--上面的例子是'h'
	//s1.end() 指向的是最后一个字符的下一个位置在'\0'
	while (it != s1.end())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;
	//范围for
	for (auto e : s1)
	{
		cout << e << " ";
	}
	cout << endl;

	//还有反向迭代器(反向输出)
	//这里面的rit是从右往左移
	//reverse_iterator 反向迭代器
	string::reverse_iterator rit = s1.rbegin();
	//	auto rit = s1.rbegin(); 如果知道类型还可以让auto自动推导
	while (rit != s1.rend())
	{
		cout << *rit << " ";
		rit++;
	}
	cout << endl;
```

**迭代器遍历的意义是什么？**

* **所有容器(数据结构)都可以使用迭代器这种方式去访问修改**
* 对于string，无论是正反遍历，下标+[]都很方便，但是对于其他容器如：**list，map/set不支持下标+[]遍历**，只能用迭代器遍历

#### string类对象的修改操作

| 函数名称       | 功能说明                                                   |
| -------------- | ---------------------------------------------------------- |
| push_back      | 在字符串后面尾插字符                                       |
| append         | 在字符串后面追加一个字符串                                 |
| operator+=(主) | 在字符串后追加字符串str/字符                               |
| c_str(主)      | 返回c格式字符串                                            |
| find+npos(主)  | 从字符串pos位置开始往后找字符c，返回该字符在字符串中的位置 |
| rfind          | 从字符串pos位置开始往前找字符c，返回该字符在字符串中的位置 |
| substr         | 在str中从pos位置开始，截取n个字符，然后将其返回            |
| insert         | 在某个位置插入字符/字符串                                  |
| erase          | 删除某个位置的字符/字符串                                  |

```c++
string s;
cout<<s<<endl;//这里是调用流的运算符重载
cout<<s.c_str<<endl;//把其当成字符串打印
//两种方法都能打印出s，但是意义不一样
```

* **find和substr的具体使用**

```c++
	string file("flie.txt");
	FILE* fout = fopen(file.c_str(), "w");
	//查找某个字符可以用find(从左往右去找)，如果能找到它会返回下标(返回值是无符号)
	//size_t find(const string & str, size_t pos = 0) const;
	//size_t find(const char* s, size_t pos = 0) const;
	//size_t find(const char* s, size_t pos, size_t n) const;
	//size_t find(char c, size_t pos = 0) const;
	//如果找不到会返回npos,npos是string类自带的const类型的静态变量
	//可以直接用类域去找
	size_t pos=file.find('.');
	//如果string file("file.txt.zip");要找的话find找的就不对了，这时候需要从右往左找
	//rfind是从右往左找---> size_t pos=file.rfind('.');
	if (pos != string::npos)
	{	//找到情况
		//打印 .后面的字符
		//string substr (size_t pos = 0, size_t len = npos) const; --->用来打印部分字符 pos就是从什么位置开始，len是到什么位置结束
		cout << file.substr(pos,file.size()-pos) << endl;
        //如果没有给到什么位置结束，默认到字符串的结尾结束
        //cout<<file.substr(pos)<<endl;
	}
```

```c++
	//find的更多使用
	string url = ("https://www.cplusplus.com/reference/string/string/find/");
	//协议 protocol
	size_t pos1 = url.find(':');
	string protocol = url.substr(0, pos1 - 0);
	//域名 domain
	size_t pos2 = url.find('/', pos1 + 3);
	string domain = url.substr(pos1+3,pos2);
	//统一资源名称
	string uri = url.substr(pos2);
	cout << protocol<<endl;
	cout <<domain <<endl;
	cout << uri<<endl;
```

* 一般不推荐插入跟删除因为效率低O(N)

```c++
//在第0位插入1个字符x
s.insert(0,1,'x')
//用迭代器插入
s,insert(s.begin(),'y');
//插入字符串
s.insert(0,"test");
//在中间插入
s.insert(5,"sssss");
```

```c++
//erase删除的一些用法
//如果最后没有给删除多少个字符，默认删到结束位置
//尽量少用头部和中间的删除，需要挪动数据效率低
//在第0位置删除一个字符
s.erase(0,1);
//在尾部删除一个字符
s.erase(s.size()-1,1);
//删除一段区间
s.erase(5,s.size()-1);
```

