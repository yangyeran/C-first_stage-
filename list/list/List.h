#pragma once
//list模拟实现的重点在于list的迭代器，它跟之前实现的string和vector不同，他并不是一个连续的地址空间，所以访问就不能用原生指针的加加减减
//那应该怎么办呢？---->c++的operator可以解决这个问题（运算符重载），可以重载++，--
//  list和vector的区别与联系
//首先list和vector是互补的，vector是一块连续的地址空间，这是优点同样也是缺点，他不适合频繁的头插头删，但是支持随机访问(可以去实现很多操作)
//大部分的编译器扩容一般是在2倍左右，可能会存在部分的空间浪费
//list支持实时申请内存，减少了内存浪费，但是最主要的是支持O(1)的插入和删除，但是不能支持下标的随机访问(空间不连续)
namespace yyr
{
	template<class T>
	struct __list_node //节点
	{
		__list_node<T>* _prev;
		__list_node<T>* _next;
		T _date;
		
		__list_node(const T& date=T())
			:_prev(nullptr)
			,_next(nullptr)
			,_date(date)
		{}
	};
	template<class InputIterator, class Ref, class Ptr>
	struct __list_reverse_iterator
	{
		typedef __list_reverse_iterator<InputIterator, Ref, Ptr> self;
		InputIterator node;
		__list_reverse_iterator(InputIterator it)
			:node(it)
		{}
		Ref operator*()
		{
			//首先要知道rbegin它指向的是end()也就是list的头结点，然后将node赋给传进来的迭代器，之前的迭代器已经实现了
			//*和--的重载，所以只需要--在解引用得到的就是值
			InputIterator prev = node;
			return *(--prev);
		}
		//T* -->operator*()返回的是T的引用，所以复用即可
		Ptr operator->()
		{
			return &operator*();
		}
		self& operator++()
		{
			--node;
			return *this;
		}
		self operator++(int)
		{
			return node--;
		}
		self& operator--()
		{
			++node;
			return *this;
		}
		self operator--(int)
		{
			return node++;
		}
		bool operator!=(const self& rit) const
		{
			return node != rit.node;
		}
		bool operator==(const self& rit) const
		{
			return node == rit.node;
		}
	};
	//class T就是正常使用，Ref就是对象类型是cosnt list<int> lt时，Ptr应用场景是重载->时
	template<class T,class Ref,class Ptr>
	struct __list_iterator
	{
		typedef __list_iterator<T,Ref,Ptr> self;
		typedef __list_node<T> list_node;
		//成员变量
		list_node* _node;
		__list_iterator(list_node* node)
			:_node(node)
		{}
		// it2 = it1 浅拷贝
		// 拷贝构造和赋值重载是否需要我们自己实现
		// 析构呢？-> 迭代器是借助节点的指针访问修改链表
		// 节点属于链表，不属于迭代器，所以他不管释放
		// 都不需要自己实现，默认生成的即可
		//Ref是返回值
		Ref operator*() 
		{
			return _node->_date;
		}
		Ptr* operator->() 
		{
			//&的优先级比->低
			//相当于&(_node->_date);
			return &_node->_date;
		}
		//前置++
		self& operator++()
		{
			_node = _node->_next;
			return *this;
		}
		//后置++
		self operator++(int)
		{
			self temp(*this);
			_node = _node->_next;
			return temp;
		}
		//前置--
		self& operator--()
		{
			_node = _node->_prev;
			return *this;
		}
		//后置++
		self operator--(int)
		{
			self temp(*this);
			_node = _node->_prev;
			return temp;
		}
		bool operator==(const self& x) const
		{
			return _node == x._node;
		}
		bool operator!=(const self& x) const
		{
			return _node != x._node;
		}
	};
	template<class T>
	class list
	{
		typedef __list_node<T> list_node;
	public:
		typedef __list_iterator<T,T&,T*> iterator;
		//这里的T不能加上const否则在实现迭代器的构造函数时会出错
		//这里是支持读但是不支持写
		typedef __list_iterator<T,const T&,const T*> const_iterator;

		typedef __list_reverse_iterator<iterator, T&, T*> reverse_iterator;
		typedef __list_reverse_iterator<const_iterator, const T&, const T*> const_reverse_iterator;
		//构造
		list()
		{
			_head = new list_node();
			_head->_next = _head;
			_head->_prev = _head;
		}
		//下面两个函数的时候，有时候会出现编译器匹配出错
		//用list<int> 来举例子
		//1的两个参数类型一个是unsigned int，int
		//2的是两个int，会发现下面的更匹配，解决方法实现一个int的版本
		list(int n, const T& val = T())//改,有现成的不会去匹配模板
		{
			//构造n个T类型的节点
			_head = new list_node();
			for (size_t i = 0; i < n; ++i)
			{
				list_node* newnode = new list_node(val);
				_head->_next = newnode;
				newnode->_prev = _head;
				newnode->_next = _head;
				_head->_prev = newnode;
			}
		}
		list(size_t n,const T& val= T())//1
		{
			//构造n个T类型的节点
			_head = new list_node();
			for (size_t i = 0; i < n; ++i)
			{
				list_node* newnode = new list_node(val);
				_head->_next = newnode;
				newnode->_prev = _head;
				newnode->_next = _head;
				_head->_prev = newnode;
			}
		}
		template<class InputIterator>//2
		list(InputIterator first, InputIterator end)
		{
			_head = new list_node();
			_head->_next = _head;
			_head->_prev = _head;
			while (first != end)
			{
				push_back(*first);
				++first;
			}
		}
		//拷贝构造list<int> lt(lt1);
		list(const list<T>& lt)
		{
			//需要实现用迭代器的构造函数
			_head = new list_node();
			_head->_next = _head;
			_head->_prev = _head;
			list<T> tmp(lt.cbegin(), lt.cend());
			std::swap(_head, tmp._head);
		}
		//赋值拷贝--->直接传值传参，然后交换就好
		list<T>& operator=(list<T> it)
		{
			swap(_head, it._head);
			return *this;
		}
		//有关迭代器的接口
		iterator begin()
		{
			return iterator(_head->_next);
		}
		iterator end()
		{
			return iterator(_head);
		}
		const_iterator cbegin() const
		{
			return const_iterator(_head->_next);
		}
		const_iterator cend() const
		{
			return const_iterator(_head);
		}
		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}
		reverse_iterator rend()
		{
			//reverse_iterator(begin());这种就是相当于去调用构造函数，而下面就是直接返回
			return reverse_iterator(begin());
		}
		bool empty() const
		{
			return (_head->_next == _head) ? true : false;
		}
		size_t size() const
		{
			//用迭代器实现
			size_t count = 0;
			list_node* start = _head->_next;
			list_node* end = _head;
			while (start != end)
			{
				++count;
				start = start->_next;
			}
			return count;
		}
		T& front()
		{
			//front返回的是第一个位置的数据
			//这里的*是被重载之后的，可以拿到T _date
			return *(begin());
		}
		const T& front() const
		{
			return *(begin());
		}
		T& back()
		{
			return *(--end());
		}
		const T& back() const
		{
			return *(--end());
		}

		void push_back(const T& val)
		{
			insert(end(), val);
			//list_node* newnode = new list_node(val);
			//list_node* prev = _head->_prev;//指向的最后一个元素
			//newnode->_prev = prev;
			//prev->_next = newnode;
			//newnode->_next = _head;
			//_head->_prev = newnode;
		}
		void push_front(const T& val)
		{
			insert(begin(), val);
		}
		void pop_front(const T& val)
		{
			erase(begin());
		}
		void pop_back(const T& val)
		{
			//尾删的时候end()指向的是最后一个元素的下一个位置，也就是头结点
			erase(--end());
		}
		iterator insert(iterator pos,const T& val=T())
		{
			//不会存在迭代器失效问题，因为迭代器指向位置不会发生改变
			list_node* newnode = new list_node(val);
			list_node* cur = pos._node;
			newnode->_next = cur;
			newnode->_prev = cur->_prev;
			cur->_prev->_next = newnode;
			cur->_prev = newnode;
			return iterator(newnode);
		}
		iterator erase(iterator pos)
		{
			//需要判断不能为头结点
			// 这里erase以后，pos是否失效？一定失效
			assert(pos != end());
			list_node* cur = pos._node;
			list_node* next = cur->_next;
			cur->_prev->_next = next;
			next->_prev = cur->_prev;
			delete cur;
			return iterator(next);
		}
		//删除除头结点以外的节点
		void clear()
		{
			iterator it = begin();
			while (it != end())
			{
				//erase(it++);
				it=erase(it);
			}
		}
		~list()
		{
			clear();
			delete _head;
			_head = nullptr;
		}
	private:
		list_node* _head;
	};
}
