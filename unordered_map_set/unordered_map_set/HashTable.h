#pragma once
#include<string>
#include<vector>
template<class Key>
struct Hash
{
	//����HashFunc()����key
	size_t operator()(const Key& k)
	{
		return k;
	}
};
//ģ����ػ�
template<>
struct Hash<string>
{
	size_t operator()(const string& s)
	{
		// BKDR
		//ÿһ����ĸ����31������ӣ�JAVA�õľ��������㷨
		size_t value = 0;
		for (auto ch : s)
		{
			value *= 31;
			value += ch;
		}
		return value;
	}
};
//��ɢ��
namespace  ClosedHash
{
	enum State
	{
		EMPTY, //Ϊ��
		EXIST,//����
		DELETE //ɾ��
	};
	template<class Key,class T>
	struct HashData
	{
		HashData()
			:_st(EMPTY)
		{}
		//��ǰ�ڵ��״̬
		State _st;
		T _pa;
	};
	//��ϣ���ṩһ���º����ӿڣ���������������Զ������ͣ�ֻ��Ҫ���Զ���������Ӧ�ķº�������
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
			//�����ڵ�ʱ��ȥ�Ƚ���û��key��ͬ�ģ����������ͬ����״̬�Ѿ���Ϊ�����ˣ���ô���Ǳ�����û��
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
			//�������ֱ�ӷ���false
			KeyofT kot;
			HashData* ret = find(kot(pa));
			if (ret)
				return false;
			//����vector��Ҫ����ռ���ܹ����к�������������resize��ֱ�Ӿͳ�ʼ������ʹ����
			//�������ӵļ�������� �洢������/size Ϊʲô������capacity�أ���Ϊ�п���ʹ�õĿռ�δ����ʼ�������ʻ��������
			//�������������趨���ܳ���0.7����ͻ��Զ�����
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
				//vector�Դ���swap
				_hd.swap(newhash._hd);
			}
			//����̽��or����̽��
			HashFunc hf;
			int start = hf(kot(pa)) % _hd.size();
			//int i = 1;
			int i = 0;
			int index = start;
			while (_hd[index]._st == EXIST)
			{
				//��i=1��Ȼ��indexÿ��ѭ��������i���������̽�⣬���i����++��index+i���Ƕ���̽��
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
				//αɾ����
				ret->_st = DELETE;
				--_size;
				return true;
			}
			return false;
		}
	private:
		vector<HashData> _hd;
		//�洢����Ч����
		int _size;
	};
}
namespace LinkHash 
{
	//��ʽ��ϣҲ���ǹ�ϣͰ
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
	//��ΪHashTableIterator�����õ���HashTable,��HashTable���ں��涨��ģ�������Ҫ����һ�£������ģ���������
	template<class Key, class T, class KeyofT, class HashFunc>
	class HashTable;
	template<class Key, class T, class Ref, class Ptr, class KeyofT, class HashFunc>
	struct HashTableIterator
	{
		typedef HashTableIterator<Key, T, Ref, Ptr, KeyofT, HashFunc> Self;
		HashData<T>* _node;
		//���ֻ��һ��ָ�룬���޷��ҵ�������Ͱ�ˣ����Ի���Ҫ����㶫��������ѡ����Ǵ��һ����ϣ���ָ��
		//������ô�����ָ�룬this��ָ�������ϣ���ָ��
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
			//���Ͱ����������
			if (_node->_next)
			{
				_node = _node->_next;
			}
			else
			{	//û������ , �����ж�����һ��Ͱ
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
					else //��Ϊ��Ҳ����һ���µ�Ͱ����Ҫ��node���Ĺ���
					{
						_node = _pht->_table[index];
						break;
					}
				}
				//��Ϊ���������һ�����ҵ���,һ����û���ҵ�
				if (index == _pht->_table.size())
					_node = nullptr;
			}
			return *this;
		}
		Self& operator--()
		{
			//��Ϊ��forward_list����û�취�ҵ���һ���ڵ�
			int index = hf(kot(_node->_kv)) % _pht->_table.size();
			if (_node == _pht->_table[index])
			{
				--index;
				//˵����ͰͷҪ��ǰȥ�ҷǿ�Ͱ
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
				//����Ͱ������Ͱ��,��¼Ͱ�������±������ҵ�_node��ǰһ��
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
	//defaultĬ�� C++11��һ���﷨����ǿ�Ʊ�����ʵ��һ���޲εĹ��� HashTable() = default;
	//T�������ͱ���map����pair<Key��Value>
	template<class Key,class T,class KeyofT,class HashFunc = Hash<Key>>
	class HashTable
	{
		//��Ԫ����������
		template<class Key, class T, class Ref, class Ptr, class KeyofT, class HashFunc>
		friend struct HashTableIterator;
		typedef HashData<T> HashData;
		typedef HashTable<Key, T, KeyofT, HashFunc> Self;
	public:
		typedef HashTableIterator<Key, T, T&, T*, KeyofT, HashFunc> Iterator;
		HashTable() = default;
		// HashTable<int ,int > _ht(ht);
		//��һ����ʼ��ȥ��ʼ������
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
				//����Ļ������ҿ�ͰȻ��һ��һ����ͷ�壬�������ͷ��Ч�ʸ�
				for (int i = 0; i < _size; ++i)
				{
					//�Ҳ�Ϊ�յ�Ͱ
					HashData* cur = _table[i];
					while (cur)
					{
						//����ӳ��λ��Ȼ��ͷ��
						size_t index = hf(kft(cur->_kv)) % newhd.size();
						HashData* next = cur->_next;
						cur->_next = newhd[index];
						newhd[index] = cur;
						cur = next;
					}
					//���������˾��ÿ�
					_table[i] = nullptr;
				}
				_table.swap(newhd);
			}
			//�����ݿ�ʼ����
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
					if (prev == nullptr)//Ͱͷ����Ҫɾ��
						_table[index] = cur->_next;
					else //ɾ�м�
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
		//��Ÿ���������ƽ������ʱ�����ǿ���ѡ������������vector���Ŀռ��ʱ���ڽ�������
		//���ƽ�������Ļ�����һ��Ͱ�����һ��
		int _size = 0;
	};
}