#pragma once
#include"HashTable.h"
template<class Key, class Value,class hash=Hash<Key>>
class unordered_map
{
	struct MapKeyofT
	{
		const Key& operator()(const pair<Key,Value>& pa)
		{
			return pa.first;
		}
	};
public:
	//δ��ʵ��������typename�ܲ���
	typedef typename LinkHash::HashTable<Key,pair<Key,Value>, MapKeyofT>::Iterator iterator;
	pair<iterator,bool> insert(const pair<Key, Value>& kv)
	{
		return _ht.Insert(kv);
	}
	iterator begin()
	{
		return _ht.begin();
	}
	iterator end()
	{
		return _ht.end();
	}
	iterator find(const Key& k)
	{
		return _ht.find(k);
	}
<<<<<<< HEAD
	Value& operator[](const Key& k)
	{
		pair<iterator, bool> ret = insert(make_pair(k, Value()));
		return ret.first->second;
	}
=======
>>>>>>> 7823ce1e6704ba4523192e8a4588b352f7a11c74
private:
	LinkHash::HashTable<Key, pair<Key,Value>, MapKeyofT> _ht;
	//ClosedHash::HashTable<Key, Key, MapKeyofT> _ht;
};
