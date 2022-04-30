#pragma once
namespace yyr
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;
		//构造函数
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
			resize(n, val);
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
		/*vector<T>& operator=(const vector<T>& v)
		{
			vector<T> tmp(v);
			swap(v);
			return *this;
		}*/
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
		//size
		size_t size() const
		{
			return _finish - _start;
		}
		//empty
		bool empty()
		{
			if (_finish == nullptr)
				return true;
			return false;
		}
		size_t capacity() const
		{
			return _endofstorage-_start;
		}
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
		void swap(vector<T>& v2)
		{
			std::swap(_start, v2._start);
			std::swap(_finish, v2._finish);
			std::swap(_endofstorage, v2._endofstorage);
		}
		void reserve(size_t n)
		{
			if (n > capacity())
			{
				T* temp = new T[n];
				size_t sz = size();
				//for (size_t i = 0; i < size(); ++i)
				//{
				//	temp[i] = _start[i];
				//}
				if (_start)
				{
					//拷贝T类型的size个字节
					memcpy(temp, _start,sizeof(T)*size());
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
		//push_back,pop_back,insert,erase
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
		//析构函数
		~vector()
		{
			delete[] _start;
			_start = _finish = _endofstorage = nullptr;
		}
	private:
		//起始
		iterator _start;
		//存了多少数据,指向的是最后一个元素的下一个位置
		iterator _finish;
		//总大小
		iterator _endofstorage;
	};
}