#pragma once
#include"RBTree.h"
template<class Key,class Value>
class Map 
{
public:
	struct MapKeyofValue
	{
		const Key& operator()(const pair<Key, Value>& kv)
		{
			return kv.first;
		}
	};
	typedef typename RBTree<Key, pair<Key, Value>, MapKeyofValue>::iterator iterator;
	typedef typename RBTree<Key, pair<Key, Value>, MapKeyofValue>::const_iterator const_iterator;
	pair<iterator,bool> Insert(const pair<Key,Value>& kv)
	{
		return _mp.Insert(kv);
	}
	iterator begin()
	{
		return _mp.begin();
	}
	iterator end()
	{
		return _mp.end();
	}
	iterator find(const Key& key)
	{
		return _mp.Find(key);
	}
	//map的[]返回的是Value的引用-->pair<Key,Value>
	//[]还有插入功能
	Value& operator[](const Key& k)
	{
		//pair<iterator, bool> ret = _mp.Insert(make_pair(k, Value())); 
		auto ret = _mp.Insert(make_pair(k, Value()));
		return ret.first->second;
	}
	void clear()
	{
		_mp.~RBTree();
	}
private:
	RBTree<Key,pair<Key, Value>,MapKeyofValue> _mp;
};