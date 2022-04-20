#pragma once
namespace yyr 
{
	class String
	{
	public:
		//只要自己实现的string支持迭代器就会支持范围for(前提是命名要规范，否则范围for还是会报错)
		// 范围for就是在编译的时候替换成迭代器
		//迭代器是一个类似于指针一样的东西，在string中可以把它理解为指针
		typedef char* iterator;
		typedef const char* const_iterator;
		iterator begin()
		{
			return _str;
		}
		iterator end()
		{
			return _str + _size;
		}
		const_iterator begin() const
		{
			return _str;
		}
		const_iterator end() const
		{
			return _str+_size;
		}
		 void Swap(String& str)
		{
			 //如果还是想要swap()
			std::swap(_str, str._str);
			std::swap(_size, str._size);
			std::swap(_capacity, str._capacity);
		}
		//strlen(str)算的是有效字符长度，需要再加个1
		//String s("hello")
		String(const char* str="")//因为后续可以对string进行增删查改等一系列操作，所以需要在堆上开空间
			:_size(strlen(str))
			,_capacity(_size)
		{
			_str = new char[_capacity + 1];
			strcpy(_str,str);
		}
		////String s1(s);
		////传统写法
		//String(const String& str)
		//	:_size(str._size)
		//	, _capacity(str._capacity)
		//{
		//	_str = new char[_capacity + 1];
		//	strcpy(_str,str._str);
		//}
		////s1=s2
		//String& operator=(const String& str)
		//{
		//	//if (this != &str) {
		//	//	//还空间只要地址正确就不会出错
		//	//	delete[] _str;
		//	//	//但是开辟空间不一样，开辟空间失败就会抛异常直接跳出去了
		//	//	//这会导致不仅没有赋值成功，还把原来的空间释放了，所以可以用一个临时变量来控制
		//	//	_str = new char[strlen(str._str) + 1];
		//	//	strcpy(_str, str._str);
		//	//}
		//	//return *this;
		//	if (this != &str) {
		//		char* temp = new char[str._capacity + 1];
		//		strcpy(temp, str._str);
		//		//如果前面开空间失败抛异常了，是不会来到delete这一步的
		//		delete[] _str;
		//		_str = temp;
		//		_size = str._size;
		//		_capacity = str._capacity;
		//	}
		//	return *this;
		//}


		//现代写法----实现简单的string(不考虑增删查改) 本质就是代码的复用
		String(const String& str)
			:_str(nullptr)
			,_size(0)
			,_capacity(0)
		{
			String temp(str._str);
			Swap(temp);
		}
		//String& operator=(const String& str)
		//{
		//	if (this != &str)
		//	{
		//		//s1=s2
		//		//这个不仅能把地址拷过去了，而且temp会自动调用析构函数，还会把s1不用的空间给释放了
		//		String temp(str);
		//		swap(_str, temp._str);
		//	}
		//	return *this;
		//}
		String& operator=(String str)
		{
			//s1=s2
			//形参就是实参的临时拷贝，所以这里的str就相当于上面的temp
			//这里不能判断是否是自己给自己赋值，因为str已经是s2的临时拷贝了，地址已经不一样了
			Swap(str);
			return *this;
		}
		void reserve(size_t n)
		{
			if (n > _capacity)
			{
				char* temp = new char[n+1];//先用一个临时数据存储,如果内存不够会直接抛异常
				strcpy(temp, _str);
				delete[] _str;
				_str = temp;
				_capacity = n;//计算的是有效内存
			}
		}
		//resize(5); resize(6,'x');  resize(20,'y')
		void resize(size_t n, char c = '\0')
		{
			if (n > _capacity)
			{
				reserve(n);
				memset(_str+_size,c,n-_size);
			}
			_size = _capacity;
			_str[_size] = '\0';
		}
		size_t find(char c)
		{
			for (size_t i = 0; i < _size; ++i)
			{
				if (_str[i] == c)
				{
					return i;
				}
			}
			return npos;
		}
		size_t find(const char* str, size_t pos = 0)
		{
			char* ret = strstr(_str + pos, str);
			if (ret == nullptr)
			{
				return npos;
			}
			return ret - _str;
		}
		void push_back(char c)
		{
			insert(_size, c);
			//if (_size == _capacity)
			//{
			//	//扩容---按照每次扩二倍
			//	reserve(_capacity == 0 ? 4 : _capacity * 2);
			//}
			////尾插
			//_str[_size] = c;
			//++_size;
			//_str[_size] = '\0';
		}
		//尾插一个字符串
		void append(const char* str)
		{
			insert(_size, str);
			/*size_t len = strlen(str);
			if (len + _size > _capacity)
			{
				reserve(len+_size);
			}
			strcpy(_str+_size, str);
			_size += len;*/
		}
		String& operator+=(const char* str)
		{
			append(str);
			return *this;
		}
		String& operator+=(char c)
		{
			push_back(c);
			return *this;
		}
		void clear()
		{
			//清空字符串但是不改变内存
			_size = 0;
			_str[_size] = '\0';
		}
		const char* c_str() const
		{
			return _str;
		}
		size_t size() const
		{
			return _size;
		}
		size_t capacity() const
		{
			return _capacity;
		}
		bool empty()const
		{
			//判断字符串是否为空，空返回true非空false
			if (_size == 0)
				return true;
			return false;
		}
		char& operator[](size_t pos)
		{
			assert(pos < _size);
			return _str[pos];
		}
		const char& operator[](size_t pos) const
		{
			assert(pos < _size);
			return _str[pos];
		}
		String& insert(size_t pos,char c)
		{
			assert(pos<=_size);
			if (_size == _capacity)
			{
				//一定要注意这样的String s;
				reserve(_capacity == 0 ? 4 : _capacity * 2);
			}
			size_t end = _size + 1;
			while (end > pos)
			{
				_str[end] = _str[end - 1];
				--end;
			}
			_str[pos] = c;
			++_size;
			return *this;
		}
		String& insert(size_t pos, const char* str)
		{
			assert(pos <= _size);
			size_t len = strlen(str);
			if (len+_size > _capacity)
			{
				reserve(len+_size);
			}
			size_t end = len + _size;
			//如果不是pos+len，是pos的话会存在越界，end=1时，end-len=-1转换成无符号就是很大的数
			//但是不会报错因为只是拷贝了，后来的ab还会把越界拷贝的给覆盖
			while (end > pos+len)
			{
				_str[end] = _str[end-len];
				--end;
			}
			strncpy(_str+pos,str,len);
			_size += len;
			return *this;
		}
		String& erase(size_t pos = 0, size_t len = npos)
		{
			assert(pos < _size);
			if (len == npos || pos+len >= _size)
			{
				_str[pos] = '\0';
				_size = pos;
			}
			else
			{
				strcpy(_str+pos,_str+len+pos);
				_size -= len;
			}
			return *this;
		}
		~String()
		{
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}
	private:
		char* _str;
		size_t _size;
		size_t _capacity; //这里capacity记录的是有效字符个数
		static const size_t npos;
	};
	const size_t String::npos = -1;
}