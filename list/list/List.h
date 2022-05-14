#pragma once
//listģ��ʵ�ֵ��ص�����list�ĵ�����������֮ǰʵ�ֵ�string��vector��ͬ����������һ�������ĵ�ַ�ռ䣬���Է��ʾͲ�����ԭ��ָ��ļӼӼ���
//��Ӧ����ô���أ�---->c++��operator���Խ��������⣨��������أ�����������++��--
//  list��vector����������ϵ
//����list��vector�ǻ����ģ�vector��һ�������ĵ�ַ�ռ䣬�����ŵ�ͬ��Ҳ��ȱ�㣬�����ʺ�Ƶ����ͷ��ͷɾ������֧���������(����ȥʵ�ֺܶ����)
//�󲿷ֵı���������һ������2�����ң����ܻ���ڲ��ֵĿռ��˷�
//list֧��ʵʱ�����ڴ棬�������ڴ��˷ѣ���������Ҫ����֧��O(1)�Ĳ����ɾ�������ǲ���֧���±���������(�ռ䲻����)
namespace yyr
{
	template<class T>
	struct __list_node //�ڵ�
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
			//����Ҫ֪��rbegin��ָ�����end()Ҳ����list��ͷ��㣬Ȼ��node�����������ĵ�������֮ǰ�ĵ������Ѿ�ʵ����
			//*��--�����أ�����ֻ��Ҫ--�ڽ����õõ��ľ���ֵ
			InputIterator prev = node;
			return *(--prev);
		}
		//T* -->operator*()���ص���T�����ã����Ը��ü���
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
	//class T��������ʹ�ã�Ref���Ƕ���������cosnt list<int> ltʱ��PtrӦ�ó���������->ʱ
	template<class T,class Ref,class Ptr>
	struct __list_iterator
	{
		typedef __list_iterator<T,Ref,Ptr> self;
		typedef __list_node<T> list_node;
		//��Ա����
		list_node* _node;
		__list_iterator(list_node* node)
			:_node(node)
		{}
		// it2 = it1 ǳ����
		// ��������͸�ֵ�����Ƿ���Ҫ�����Լ�ʵ��
		// �����أ�-> �������ǽ����ڵ��ָ������޸�����
		// �ڵ��������������ڵ������������������ͷ�
		// ������Ҫ�Լ�ʵ�֣�Ĭ�����ɵļ���
		//Ref�Ƿ���ֵ
		Ref operator*() 
		{
			return _node->_date;
		}
		Ptr* operator->() 
		{
			//&�����ȼ���->��
			//�൱��&(_node->_date);
			return &_node->_date;
		}
		//ǰ��++
		self& operator++()
		{
			_node = _node->_next;
			return *this;
		}
		//����++
		self operator++(int)
		{
			self temp(*this);
			_node = _node->_next;
			return temp;
		}
		//ǰ��--
		self& operator--()
		{
			_node = _node->_prev;
			return *this;
		}
		//����++
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
		//�����T���ܼ���const������ʵ�ֵ������Ĺ��캯��ʱ�����
		//������֧�ֶ����ǲ�֧��д
		typedef __list_iterator<T,const T&,const T*> const_iterator;

		typedef __list_reverse_iterator<iterator, T&, T*> reverse_iterator;
		typedef __list_reverse_iterator<const_iterator, const T&, const T*> const_reverse_iterator;
		//����
		list()
		{
			_head = new list_node();
			_head->_next = _head;
			_head->_prev = _head;
		}
		//��������������ʱ����ʱ�����ֱ�����ƥ�����
		//��list<int> ��������
		//1��������������һ����unsigned int��int
		//2��������int���ᷢ������ĸ�ƥ�䣬�������ʵ��һ��int�İ汾
		list(int n, const T& val = T())//��,���ֳɵĲ���ȥƥ��ģ��
		{
			//����n��T���͵Ľڵ�
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
			//����n��T���͵Ľڵ�
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
		//��������list<int> lt(lt1);
		list(const list<T>& lt)
		{
			//��Ҫʵ���õ������Ĺ��캯��
			_head = new list_node();
			_head->_next = _head;
			_head->_prev = _head;
			list<T> tmp(lt.cbegin(), lt.cend());
			std::swap(_head, tmp._head);
		}
		//��ֵ����--->ֱ�Ӵ�ֵ���Σ�Ȼ�󽻻��ͺ�
		list<T>& operator=(list<T> it)
		{
			swap(_head, it._head);
			return *this;
		}
		//�йص������Ľӿ�
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
			//reverse_iterator(begin());���־����൱��ȥ���ù��캯�������������ֱ�ӷ���
			return reverse_iterator(begin());
		}
		bool empty() const
		{
			return (_head->_next == _head) ? true : false;
		}
		size_t size() const
		{
			//�õ�����ʵ��
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
			//front���ص��ǵ�һ��λ�õ�����
			//�����*�Ǳ�����֮��ģ������õ�T _date
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
			//list_node* prev = _head->_prev;//ָ������һ��Ԫ��
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
			//βɾ��ʱ��end()ָ��������һ��Ԫ�ص���һ��λ�ã�Ҳ����ͷ���
			erase(--end());
		}
		iterator insert(iterator pos,const T& val=T())
		{
			//������ڵ�����ʧЧ���⣬��Ϊ������ָ��λ�ò��ᷢ���ı�
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
			//��Ҫ�жϲ���Ϊͷ���
			// ����erase�Ժ�pos�Ƿ�ʧЧ��һ��ʧЧ
			assert(pos != end());
			list_node* cur = pos._node;
			list_node* next = cur->_next;
			cur->_prev->_next = next;
			next->_prev = cur->_prev;
			delete cur;
			return iterator(next);
		}
		//ɾ����ͷ�������Ľڵ�
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
