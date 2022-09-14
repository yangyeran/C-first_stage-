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
	//未被实例化不加typename跑不过
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
private:
	LinkHash::HashTable<Key, pair<Key,Value>, MapKeyofT> _ht;
	//ClosedHash::HashTable<Key, Key, MapKeyofT> _ht;
};
