#pragma once
//哈希表在STL中也有应用，最有代表的就是unordered_map和unordered_set
//通过之前的学习我们知道map和set的底层是一棵红黑树来实现的，而unordered_map和unordered_set的底层是通过哈希表来实现的
//unordered是无序的，哈希表它其实就是一种映射关系的表，之前的计数排序用的就是这种，拿int类型的数据来举例子，存储数据时
//可以给要存的数据取模来确定位置，那这就避免不了会产生冲突，也就是多个数据会定位到相同的位置，这叫做哈希冲突
//解决哈希冲突有两种最为常见的方式:闭散列(开放定址法)和开散列
//闭散列 --->线性探测和二次探测 
// 线性探测：从发生冲突的位置开始，依次向后探测，直到寻找到下一个空位置为止
// 线性探测缺点：一旦发生哈希冲突，所有的冲突连在一起，容易产生数据“堆积”
// 即：不同关键码占据可利用的空位置，使得寻找某关键码的位置需要许多次比较，导致搜索效率降低
// 线性探测的缺陷是产生冲突的数据堆积在一块，这与其找下一个空位置有关系，因为找空位置的方式就是
//二次探测：挨着往后逐个去找，因此二次探测为了避免该问题，找下一个空位置的方法为： Hi= (H0+i*i) % m,
//或者：Hi= (H0-i*i) % m。其中：i = 1, 2, 3…， 是通过散列函数Hash(x)对元素的关键码 key 进行计算得到的位置，m是表的大小。
//当发生哈希冲突时，如果哈希表未被装满，说明在哈希表中必然还有空位置，那么可以把key存放到冲突位置中的“下一个” 空位置中去。


//有一个问题： 做map/set的key有什么要求，unordered_map/unordered_set又有什么要求
//前面的:需要Key支持较大小或者支持比较大小的仿函数
//后面的:需要Key能够转换成无符号的整型，或者支持Key转换成无符号整型的仿函数

//后面的两个命名空间都要用到，所以就放在外面了
//但是只有Key和Value的话，如果是string类型的话，会出现严重的哈希冲突
//因为string的比较是比较首个字母的大小，所以我们就需要用到仿函数
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
	template<class Key,class Value>
	struct HashData
	{
		HashData()
			:_st(EMPTY)
		{}
		//当前节点的状态
		State _st;
		pair<Key, Value> _pa;
	};
	//哈希表提供一个仿函数接口，这样如果传的是自定义类型，只需要传自定义类型相应的仿函数即可
	template<class Key,class Value,class HashFunc = Hash<Key>>
	class HashTable
	{
		typedef HashData<Key, Value> HashData;
	public:
		HashTable()
			:_size(0)
		{}
		HashData* find(const Key& k)
		{
			HashFunc hf;
			if (_hd.size() == 0)
				return nullptr;
			int start = hf(k)% _hd.size();
			int i = 0;
			int index = start;
			//当存在的时候去比较有没有key相同的，如果都不相同，且状态已经不为存在了，那么就是表里面没有
			while (_hd[index]._st == EXIST)
			{
				if (hf(_hd[index]._pa.first) == hf(k))
				{
					return &_hd[index];
				}
				++i;
				index = (index + i*i) % _hd.size();
			}
			return nullptr;
		}
		bool insert(const pair<Key, Value>& pa)
		{
			//如果存在直接返回false
			HashData* ret = find(pa.first);
			if (ret)
				return false;
			//首先vector需要开完空间才能够进行后续操作这里用resize，直接就初始化可以使用了
			//负载因子的计算可以用 存储的数据/size 为什么不能用capacity呢？因为有可能使用的空间未被初始化，访问会出现问题
			//负载因子我们设定不能超过0.7否则就会自动扩容
			if (_hd.size() == 0 || _size * 10 / _hd.size() >= 7)
			{
				int newsize = (_hd.size() == 0 ? 10 : 2 * _hd.size());
				HashTable<Key, Value> newhash;
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
			int start = hf(pa.first) % _hd.size();
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
	enum State
	{
		EXIST,//存在
		EMPTY, //为空
		DELETE //删除
	};
	template<class Key, class Value>
	struct HashData
	{
		HashData(const pair<Key, Value>& kv)
			:_kv(kv)
			,_next(nullptr)
		{}
		pair<Key, Value> _kv;
		//这里挂一个forward_list
		HashData<Key, Value>* _next;
	};
	//default默认 C++11有一个语法可以强制编译器实现一个无参的构造 HashTable() = default;
	template<class Key,class Value,class HashFunc = Hash<Key>>
	class HashTable
	{
		typedef HashData<Key, Value> HashData;
	public:
		HashTable()
			:_size(0)
		{}
		HashData* find(const Key& k)
		{
			if (_table.empty())
				return nullptr;
			HashFunc hf;
			size_t index = hf(k) % _table.size();
			HashData* cur = _table[index];
			while (cur)
			{
				if (cur->_kv.first == k)
				{
					return cur;
				}
				else
				{
					cur = cur->_next;
				}
			}
			return nullptr;
		}
		bool Insert(const pair<Key,Value>& pa)
		{
			HashData* ret = find(pa.first);
			if (ret)
				return false;
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
						size_t index = hf(cur->_kv.first) % newhd.size();
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
			size_t index = hf(pa.first) % _table.size();
			HashData* next = _table[index];
			HashData* data = new HashData(pa);
			_table[index] = data;
			data->_next = next;
			++_size;
			return true;
		}
		bool Erase(const Key& k)
		{
			if(_table.empty())
				return false;
			HashFunc hf;
			size_t index = hf(k) % _table.size();
			HashData* cur = _table[index];
			while (cur)
			{
				HashData* prev = nullptr;
				if (cur->_kv.first == k)
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
	private:
		vector<HashData*> _table;
		//存放个数，设置平衡因子时，我们可以选择插入个数等于vector开的空间的时候在进行扩容
		//如果平均下来的话就是一个桶下面挂一个
		int _size;
	};
}