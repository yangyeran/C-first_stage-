#pragma once
#include<string>
#include<vector>
template<class Key>
struct Hash
{
	//传给HashFunc()的是key
	size_t operator()(const Key& k)
	{
		return k;
	}
};
//模板的特化
template<>
struct Hash<string>
{
	size_t operator()(const string& s)
	{
		// BKDR
		//每一个字母乘上31后再相加，JAVA用的就是这种算法
		size_t value = 0;
		for (auto ch : s)
		{
			value *= 31;
			value += ch;
		}
		return value;
	}
};
//闭散列
namespace  ClosedHash
{
	enum State
	{
		EMPTY, //为空
		EXIST,//存在
		DELETE //删除
	};
	template<class Key,class T>
	struct HashData
	{
		HashData()
			:_st(EMPTY)
		{}
		//当前节点的状态
		State _st;
		T _pa;
	};
	//哈希表提供一个仿函数接口，这样如果传的是自定义类型，只需要传自定义类型相应的仿函数即可
	template<class Key,class T,class KeyofT ,class HashFunc = Hash<Key>>
	class HashTable
	{
		typedef HashData<Key, T> HashData;
	public:
		HashTable()
			:_size(0)
		{}
		HashData* find(const Key& k)
		{
			HashFunc hf;
			KeyofT kot;
			if (_hd.size() == 0)
				return nullptr;
			int start = hf(k)% _hd.size();
			int i = 0;
			int index = start;
			//当存在的时候去比较有没有key相同的，如果都不相同，且状态已经不为存在了，那么就是表里面没有
			while (_hd[index]._st == EXIST)
			{
				if (hf(kot(_hd[index]._pa)) == hf(k))
				{
					return &_hd[index];
				}
				++i;
				index = (index + i*i) % _hd.size();
			}
			return nullptr;
		}
		bool insert(const T& pa)
		{
			//如果存在直接返回false
			KeyofT kot;
			HashData* ret = find(kot(pa));
			if (ret)
				return false;
			//首先vector需要开完空间才能够进行后续操作这里用resize，直接就初始化可以使用了
			//负载因子的计算可以用 存储的数据/size 为什么不能用capacity呢？因为有可能使用的空间未被初始化，访问会出现问题
			//负载因子我们设定不能超过0.7否则就会自动扩容
			if (_hd.size() == 0 || _size * 10 / _hd.size() >= 7)
			{
				int newsize = (_hd.size() == 0 ? 10 : 2 * _hd.size());
				HashTable<Key, T> newhash;
				newhash._hd.resize(newsize);
				for (size_t i = 0; i < _hd.size(); ++i)
				{
					if (_hd[i]._st == EXIST)
					{
						newhash.insert(_hd[i]._pa);
					}
				}
				//vector自带的swap
				_hd.swap(newhash._hd);
			}
			//线性探测or二次探测
			HashFunc hf;
			int start = hf(kot(pa)) % _hd.size();
			//int i = 1;
			int i = 0;
			int index = start;
			while (_hd[index]._st == EXIST)
			{
				//让i=1，然后index每次循环都加上i这就是线性探测，如果i不断++，index+i就是二次探测
				++i;
				index = (index + i) % _hd.size();
			}
			_hd[index]._pa = pa;
			_hd[index]._st = EXIST;
			++_size;
			return true;
		}
		bool erase(const Key& k)
		{
			HashData* ret = find(k);
			if (ret)
			{
				//伪删除法
				ret->_st = DELETE;
				--_size;
				return true;
			}
			return false;
		}
	private:
		vector<HashData> _hd;
		//存储的有效数据
		int _size;
	};
}
namespace LinkHash 
{
	//链式哈希也就是哈希桶
	template<class T>
	struct HashData
	{
		HashData(const T& kv)
			:_kv(kv)
			,_next(nullptr)
		{}
		T _kv;
		HashData<T>* _next;
	};
	//因为HashTableIterator里面用到了HashTable,而HashTable是在后面定义的，所以需要声明一下，这就是模板类的声明
	template<class Key, class T, class KeyofT, class HashFunc>
	class HashTable;
	template<class Key, class T, class Ref, class Ptr, class KeyofT, class HashFunc>
	struct HashTableIterator
	{
		typedef HashTableIterator<Key, T, Ref, Ptr, KeyofT, HashFunc> Self;
		HashData<T>* _node;
		//如果只存一个指针，就无法找到后续的桶了，所以还需要存点别点东西，这里选择的是存放一个哈希表的指针
		//至于怎么传这个指针，this是指向这个哈希表的指针
		HashTable<Key, T, KeyofT,HashFunc>* _pht;
		HashTableIterator(HashData<T>* node,HashTable<Key, T, KeyofT,HashFunc>* pht)
			:_node(node)
			,_pht(pht)
		{}
		Ref operator*()
		{
			return _node->_kv;
		}
		Ptr operator->()
		{
			return &_node->_kv;
		}
		Self& operator++()
		{
			//如果桶下面有数据
			if (_node->_next)
			{
				_node = _node->_next;
			}
			else
			{	//没有数据 , 首先判断是哪一个桶
				HashFunc hf;
				KeyofT kot;
				size_t index = hf(kot(_node->_kv)) % _pht->_table.size();
				++index;
				while (index < _pht->_table.size())
				{
					if (_pht->_table[index] == nullptr)
					{
						++index;
					}
					else //不为空也就是一个新的桶，需要将node给改过来
					{
						_node = _pht->_table[index];
						break;
					}
				}
				//分为两种情况，一个是找到了,一个是没有找到
				if (index == _pht->_table.size())
					_node = nullptr;
			}
			return *this;
		}
		Self& operator--()
		{
			//因为是forward_list所以没办法找到上一个节点
			int index = hf(kot(_node->_kv)) % _pht->_table.size();
			if (_node == _pht->_table[index])
			{
				--index;
				//说明是桶头要往前去找非空桶
				while (index >= 0)
				{
					if (_pht->_table[index] == nullptr)
					{
						--index;
					}
					else
					{
						_node = _pht->_table[index];
						break;
					}
				}
				if (index < 0)
					_node = nullptr;
			}
			else
			{
				//不在桶顶，在桶里,记录桶顶，向下遍历，找到_node的前一个
				HashData<T>* cur = _pht->_table[index];
				while (cur->_next != _node)
				{
					cur = cur->_next;
				}
				_node = cur;
			}
			return *this;
		}
		bool operator==(const Self& s) const 
		{
			return _node == s._node;
		}
		bool operator!=(const Self& s) const
		{
			return _node != s._node;
		}
	};
	//default默认 C++11有一个语法可以强制编译器实现一个无参的构造 HashTable() = default;
	//T就是类型比如map就是pair<Key，Value>
	template<class Key,class T,class KeyofT,class HashFunc = Hash<Key>>
	class HashTable
	{
		//友元函数的声明
		template<class Key, class T, class Ref, class Ptr, class KeyofT, class HashFunc>
		friend struct HashTableIterator;
		typedef HashData<T> HashData;
		typedef HashTable<Key, T, KeyofT, HashFunc> Self;
	public:
		typedef HashTableIterator<Key, T, T&, T*, KeyofT, HashFunc> Iterator;
		HashTable() = default;
		// HashTable<int ,int > _ht(ht);
		//拿一个初始化去初始化另外
		HashTable(const Self& ht)
		{
			_table.resize(ht._table.size());
			for (size_t i = 0; i < ht._table.size(); ++i)
			{
				HashData* cur = ht._table[i];
				while (cur)
				{
					HashData* copy = new HashData(cur->_kv);
					copy->_next = _table[i];
					_table[i] = copy;
					cur = cur->_next;
				}
			}
			_size = ht._size;
		}
		Self& operator=(Self ht)
		{
			_table.swap(ht._table);
			swap(_size, ht._size);
			return *this;
		}
		Iterator begin()
		{
			for (size_t i = 0; i < _table.size(); ++i)
			{
				if (_table[i])
					return Iterator(_table[i], this);
			}
			return end();
		}
		Iterator end()
		{
			return Iterator(nullptr, this);
		}
		Iterator find(const Key& k)
		{
			if (_table.empty())
				return end();
			HashFunc hf;
			KeyofT kft;
			size_t index = hf(k) % _table.size();
			HashData* cur = _table[index];
			while (cur)
			{
				if (kft(cur->_kv) == k)
				{
					return Iterator(cur, this);
				}
				else
				{
					cur = cur->_next;
				}
			}
			return end();
		}
		pair<Iterator,bool> Insert(const T& pa)
		{
			KeyofT kft;
			Iterator ret = find(kft(pa));
			if (ret!=end())
				return make_pair(ret, false);
			HashFunc hf;
			if (_size == _table.size())
			{
				size_t newsize = (_table.size() == 0 ? 10 : _table.size() * 2);
				vector<HashData*> newhd;
				newhd.resize(newsize);
				//这里的话就是找空桶然后一个一个的头插，单链表的头插效率高
				for (int i = 0; i < _size; ++i)
				{
					//找不为空的桶
					HashData* cur = _table[i];
					while (cur)
					{
						//计算映射位置然后头插
						size_t index = hf(kft(cur->_kv)) % newhd.size();
						HashData* next = cur->_next;
						cur->_next = newhd[index];
						newhd[index] = cur;
						cur = next;
					}
					//数据移走了就置空
					_table[i] = nullptr;
				}
				_table.swap(newhd);
			}
			//扩完容开始插入
			size_t index = hf(kft(pa)) % _table.size();
			HashData* next = _table[index];
			HashData* data = new HashData(pa);
			_table[index] = data;
			data->_next = next;
			++_size;
			return make_pair(Iterator(data, this), true);
		}
		bool Erase(const Key& k)
		{
			if(_table.empty())
				return false;
			HashFunc hf;
			KeyofT kot;
			size_t index = hf(kot(k)) % _table.size();
			HashData* cur = _table[index];
			while (cur)
			{
				HashData* prev = nullptr;
				if (kot(cur->_kv) == k)
				{
					if (prev == nullptr)//桶头就是要删的
						_table[index] = cur->_next;
					else //删中间
						prev->_next = cur->_next;
					--_size;
					delete cur;
					return true;
				}
				else
				{
					prev = cur;
					cur = cur->_next;
				}
			}
			return false;
		}
		~HashTable()
		{
			for (size_t i = 0; i < _table.size(); ++i)
			{
				HashData* cur = _table[i];
				while (cur)
				{
					HashData* next = cur->_next;
					delete cur;
					cur = next;
				}
				_table[i] = nullptr;
			}
		}
	private:
		vector<HashData*> _table;
		//存放个数，设置平衡因子时，我们可以选择插入个数等于vector开的空间的时候在进行扩容
		//如果平均下来的话就是一个桶下面挂一个
		int _size = 0;
	};
}