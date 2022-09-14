#pragma once
#include"HashTable.h"
template<class Key, class hash = Hash<Key>>
class unordered_set
{
	struct SetKeyofT
	{
		const Key& operator()(const Key& k)
		{
			return k;
		}
	};
public:
	//未被实例化不加typename跑不过
	typedef typename LinkHash::HashTable<Key, Key, SetKeyofT>::Iterator iterator;
	pair<iterator,bool> insert(const Key& key)
	{
		return _ht.Insert(key);
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
	LinkHash::HashTable<Key, Key, SetKeyofT> _ht;
	//ClosedHash::HashTable<Key, Key, SetKeyofT> _ht;
};