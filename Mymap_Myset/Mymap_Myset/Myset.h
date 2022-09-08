#pragma once
#include"RBTree.h"
template<class Key>
class Set
{
	typedef Key Value;
public:
	struct SetKeyofValue
	{
		const Key& operator()(const Key& k)
		{
			return k;
		}
	};
	//调用的时候才会知道具体类型，所以用typename修饰
	typedef typename RBTree<Key, Value, SetKeyofValue>::iterator iterator;
	typedef typename RBTree<Key, Value, SetKeyofValue>::const_iterator const_iterator;
	pair<iterator,bool> Insert(const Key& k)
	{
		return _st.Insert(k);
	}
	iterator begin()
	{
		return _st.begin();
	}
	iterator end()
	{
		return _st.end();
	}
	iterator find(const Key& key)
	{
		return _st.Find(key);
	}
	void clear()
	{
		_st.~RBTree();
	}
private:
	RBTree<Key, Value, SetKeyofValue> _st;
};