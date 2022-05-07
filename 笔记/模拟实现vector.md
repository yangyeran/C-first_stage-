@[toc](目录)

补：

在vs的编译器中，对string进行了一些优化

```c++
std::string s1("1111111");
std::string s2("11111111111111111111111111");
cout<<sizeof(s1)<<endl;
cout<<sizeof(s2)<<endl;//他们的大小是一样的，都是28
```

![image-20220504174207494](C:/Users/yangyr0206/AppData/Roaming/Typora/typora-user-images/image-20220504174207494.png)

原因是：

```c++
class string
{
    private:
    char _Buf[16];//当字符串长度小于16时存在_Buf里面
    char* _Ptr;//超出就给_Ptr在堆上申请空间
    size_t _Mysize;
    size_t _Myres;
}
```

![image-20220504174353886](C:/Users/yangyr0206/AppData/Roaming/Typora/typora-user-images/image-20220504174353886.png)

![image-20220504174457541](C:/Users/yangyr0206/AppData/Roaming/Typora/typora-user-images/image-20220504174457541.png)

---

## 模拟实现vector

首先为了与库里面的vector做区分，定义了一个命名空间在命名空间里面实现的vector，这个模拟实现是简单的实现一些比较常见的接口。

```c++
namespace yyr
{
	template<class T>
	class vector
	{
        public:
        //函数部分放在后面
        typedef T* iterator;
		typedef const T* const_iterator;
        private:
		//起始
		iterator _start;
		//存了多少数据,指向的是最后一个元素的下一个位置
		iterator _finish;
		//总大小
		iterator _endofstorage;
    }
```

*  typedef T* iterator;
   typedef const T* const_iterator;

   这两个重命名必须放在公共区域，否则后面使用时会出现一些问题--->yyr::vector<int>::iterator it = v1.begin();
   在外部使用时会报错，因为class默认成员为私有，外部不能访问私有

* 在vector的源码中，它的成员变量是三个迭代器：start，finish , end_of_storage

---

### 一、构造函数

```c++
		//1、无参默认构造函数
		vector()
			:_start(nullptr)
			, _finish(nullptr)
			, _endofstorage(nullptr)
		{}
		//2.带参的构造函数
		vector(int n, const T& val = T())//会默认调用T的构造函数内置类型也有构造函数int=int(10);
			:_start(nullptr)
			, _finish(nullptr)
			, _endofstorage(nullptr)
		{
			reserve(n);
			while (n--)
			{
				push_back(val);
			}
		}
		//3.迭代器构造
		template<class InputIterator>
		vector(InputIterator first, InputIterator last)
			:_start(nullptr)
			,_finish(nullptr)
			,_endofstorage(nullptr)
		{
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}
		//拷贝构造和赋值拷贝
		//v1(v2)-->实现这个拷贝构造必须实现一个用迭代器的构造函数
		vector(const vector<T>& v)
			:_start(nullptr)
			,_finish(nullptr)
			,_endofstorage(nullptr)
		{
            //因为v是const修饰的所以它的迭代器也需要使用const修饰的，否则会报错
			vector<int> tmp(v.cbegin(),v.cend());
			swap(tmp);
		}
		//赋值拷贝
		//v1=v2
		vector<T>& operator=(const vector<T> v)
		{
			swap(v);
			return *this;
		}
```

* 如果实现拷贝构造就需要实现支持用迭代器的构造函数，因为在源代码中的定义vector(const vector<T>& v)，参数是不能修改的，所以需要一个v的临时对象，使用迭代器的拷贝构造会更加方便![image-20220501234757775](C:/Users/yangyr0206/AppData/Roaming/Typora/typora-user-images/image-20220501234757775.png)

* 函数模板的模板参数要传迭代器区间时，是有命名规范的
  * 迭代器分类：input_iterator(只读迭代器)、output_iterator(只写迭代器)、forwad_iterator(单向迭代器)、bidirectional_iterator(双向迭代器)、randomaccess_iterator(随机迭代器)
* swap是自己实现的函数，没有用算法库中提供的，相比于算法库中的swap，自己实现的效率要稍微高一点

### 二、迭代器和一些容量的接口实现

```c++
		//begin和end
		iterator begin()
		{
			return _start;
		}
		const_iterator cbegin() const
		{
			return _start;
		}
		iterator end()
		{
			return _finish;
		}
		const_iterator cend() const
		{
			return _finish;
		}
		//size是存放了多少数据
		size_t size() const
		{
			return _finish - _start;
		}
		//empty 判空
		bool empty()
		{
			if (_finish == nullptr)
				return true;
			return false;
		}
		//capacity是总容量
		size_t capacity() const
		{
			return _endofstorage-_start;
		}
		//可以支持下标访问
		T& operator[](size_t n)
		{
			assert(n < size());
			//return start[n];
			return *(_start + n);
		}
		const T& operator[](size_t n) const
		{
			assert(n < size());
			return *(_start + n);
		}
		//交换-->这里需要用域作用限定符来指定，否则会默认调用我们实现的swap，从而产生错误
		void swap(vector<T>& v2)
		{
			std::swap(_start, v2._start);
			std::swap(_finish, v2._finish);
			std::swap(_endofstorage, v2._endofstorage);
		}
```

 #### reserve和resize的实现

```c++
		void reserve(size_t n)
		{
            //当n大于capacity的时候才会进行扩容
			if (n > capacity())
			{
				T* temp = new T[n];
				size_t sz = size();
				if (_start)
				{
					//拷贝T类型的size个字节
					//memcpy(temp, _start,sizeof(T)*size());
                    //如果是内置类型int这样的，一个一个拷贝没有问题
					//如果T是自定义类型会去调用T的深拷贝赋值
                    for(size_t i=0;i<sz;++i)
                    {
                        temp[i] = _start[i];
                    }
					delete[] _start;
				}
				_start=temp;
				//需要提前存size的值否则会出问题
				_finish = _start + sz;
				_endofstorage = _start + n;
			}
		}
		void resize(size_t n, const T& val = T())
		{
			//开空间+初始化
			if (n < size())
			{
				_finish = _start + n;
			}
			else
			{
				reserve(n);
			}
			//c++中的vector实现是不会改变已经存在的数据，新开的空间会被初始化为val
			while (_finish != _endofstorage)
			{
				*_finish = val;
				++_finish;
			}
		}
```

#### insert、push_back、pop_back、erase

```c++
		//push_back
		void push_back(const T& val)
		{
			if (_finish == _endofstorage)
			{
				reserve(capacity()==0?4:capacity()*2);
			}
				*_finish = val;
				++_finish;
		}
		//pop_back
		void pop_back()
		{
			assert(_start<_finish);
			--_finish;
		}
		//insert
		//返回值指向第一个新插入元素的迭代器。
		iterator insert(iterator pos,const T& val)
		{
			//迭代器失效问题主要就是如果扩容之后原来的地址就会失效
			//更新一下迭代器就好了
			assert(pos >= _start);
			assert(pos <= _finish);
			if (_finish == _endofstorage)
			{
				//这里就是记录更新迭代器的
				size_t len = pos - _start;
				reserve(capacity() == 0 ? 4 : capacity() * 2);
				pos = _start + len;
			}
			for (iterator i = end()-1; i >= pos; --i)
			{
				*(i + 1) = *i;
			}
			*pos = val;
			++_finish;
			return pos;
		}
		//任意位置尾删
		//指向函数调用擦除的最后一个元素后面的元素的新位置的迭代器,注意不能等于_finish
		iterator erase(iterator pos)
		{
			assert(pos < _finish);
			assert(pos >= _start);
			for (size_t i = pos - _start; i < capacity(); ++i)
			{
				_start[i] = _start[i + 1];
			}
			--_finish;
			return pos;
		}
```

**注意：**

* 实现insert的时候需要考虑迭代器失效问题，因为如果插入的内存不够就会进行扩容，一旦扩容，之前的空间就会被释放，也就会导致之前传的迭代器pos就会失效(指向了一块被释放的空间)，**解决方法：更新一下迭代器就好了**

* erase在使用的时候也会出现迭代器失效的问题，也是需要注意的

  ```c++
  void fun4()
  {
  	// 三种场景去测试
  	// 1 2 3 4 5 -> 正常
  	// 1 2 3 4   -> 崩溃
  	// 1 2 4 5   -> 没删除完
  	yyr::vector<int> v1;
  	v1.push_back(1);
  	v1.push_back(2);
  	v1.push_back(3);
  	v1.push_back(4);
  	v1.push_back(5);
  	yyr::vector<int>::iterator it = v1.begin();
  	while (it != v1.end())
  	{
  		if (*it % 2 == 0)
  		{
  			//经过删除之后，it指向的值已经发生变化了，如果再++，就有可能会导致错误具体见上面三个例子
              //这也是迭代器失效的应用场景，使用时需要注意(erase的返回值是最近删除的元素的后面的迭代器)
  			it=v1.erase(it);	
  		}
  		else 
  		{
  			++it;
  		}
  	}
  	for (auto e : v1)
  	{
  		cout << e << " ";
  	}
  	cout << endl;
  }
  ```

  * 上面三个例子如果用vs的vector三种情况都会报错，因为，vs对迭代器进行了断言，erase之后不允许继续访问erase的那个迭代器
  * 同一段代码在不同的编译器下的运行结果可能是不一样的，因为底层源码不同

