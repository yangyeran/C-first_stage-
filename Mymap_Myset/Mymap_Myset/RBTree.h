#pragma once
//我们知道map和set的的底层都是红黑树，所以我们需要去思考如何才能够让RBTree能够同时支持<Key,Value>和<Key>模型呢
//我们可以去再次封装，具体操作见下
enum Colour
{
	Red,
	Black
};
template<class T>
struct RBTreeNode
{
	RBTreeNode(const T& kv)
		:_left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _cl(Red)
		, _data(kv)
	{}
	RBTreeNode<T>* _left;
	RBTreeNode<T>* _right;
	RBTreeNode<T>* _parent;
	//不知道具体是什么类型，需要传了之后才能知道
	T _data;
	Colour _cl;
};
template<class T,class Ref,class Ptr>
struct RBTreeIterator
{
	//本质就是指针，所以要存储一个红黑树的节点
	typedef RBTreeNode<T> Node;
	typedef RBTreeIterator<T, Ref, Ptr> Self;
	Node* _node;
	RBTreeIterator(Node* node)
		:_node(node)
	{}
	Self& operator++() 
	{
		//因为RBTree是有序的，所以++一定会比原先的大，又因为这个实现是左为小，右为大
		//所以只需向右走，那么就有几种情况
		//1、右不为空
		if (_node->_right)
		{
			Node* pNode = _node->_right;
			//如果右边节点有左子树，那么先去最左子树去找,如果没有左子树就是pNode
			while (pNode->_left)
			{
				pNode = pNode->_left;
			}
			_node = pNode;
		}
		//2、右为空那就去找往上去找，可能不只是找一次
		else
		{
			Node* cur = _node;
			Node* parent = _node->_parent;
			//到根节点会结束并且如果cur是parent的左也会结束
			while (parent && parent->_right == cur)
			{
				cur = parent;
				parent = parent->_parent;
			}
			_node = parent;
		}
		return *this;
	}
	Self& operator--()
	{
		//如果左子树不为空
		if (_node->_left)
		{
			Node* pNode = _node->_left;
			while (pNode->_right)
			{
				pNode = pNode->_right;
			}
			_node = pNode;
		}
		//左边为空
		else
		{
			Node* cur = _node;
			Node* parent = cur->_parent;
			//如果父亲不存在或者当cur是父亲的右时结束
			while (parent && cur == parent->_left)
			{
				cur = parent;
				parent = parent->_parent;
			}

			_node = parent;
		}
		return *this;
	}
	Ptr operator->()
	{
		return &_node->_data;
	}
	Ref operator*()
	{
		return _node->_data;
	}
	//红黑树的迭代器，只需要比较本身是否相同，而不是值
	bool operator!=(const Self& s) const
	{
		return _node != s._node;
	}
	bool operator==(const Self& s) const
	{
		return _node == s._node;
	}
};
// map-> RBTree<Key,pair<Key,Value>,mapKeyofValue>
// set-> RBTree<Key,Value,SetKeyofValue>   //typedef Key Value;
template<class Key, class Value, class KeyofValue>
class RBTree
{
	typedef RBTreeNode<Value> Node;
public:
	typedef RBTreeIterator<Value,Value&,Value*> iterator;
	typedef RBTreeIterator<Value,const Value&,const Value*> const_iterator;
	RBTree()
		:_root(nullptr)
	{}
	//拷贝构造
	RBTree(const RBTree<Key,Value,KeyofValue>& rbt)
	{
		_root = Copy(rbt._root);
	}
	//赋值拷贝
	RBTree<Key, Value, KeyofValue>& operator=(RBTree<Key, Value, KeyofValue> rbt)
	{
		swap(_root, rbt._root);
		return *this;
	}
	//返回的是迭代器
	iterator Find(const Key& k)
	{
		Node* cur = _root;
		KeyofValue kov;
		while (cur)
		{
			if (kov(cur->_data) > k)
			{
				cur = cur->_left;
			}
			else if (kov(cur->_data) < k)
			{
				cur = cur->_right;
			}
			else
			{
				return iterator(cur);
			}
		}
		return end();
	}
	iterator begin()
	{
		//最左节点即使begin
		Node* min = _root;
		while (min && min->_left)
		{
			min = min->_left;
		}
		return iterator(min);
	}
	//返回的是最后一个节点的后一个节点，这里实现并没有哨兵位的头结点
	//所以可以直接返回nullptr
	iterator end()
	{
		return iterator(nullptr);
	}
	//Value是个不确定的类型，不知道是map调用还是set调用
	//这里就需要用到仿函数了
	pair<iterator,bool> Insert(const Value& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			_root->_cl = Black;
			return make_pair(iterator(_root),true);
		}
		Node* cur = _root;
		Node* parent = nullptr;
		KeyofValue kov;
		while (cur)
		{
			//仿函数在做模板参数的时候传的是类型，在用的时候传的是对象
			//如果插入的大于_root里面存的那就往右边插入
			if (kov(kv) > kov(cur->_data))
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (kov(kv)< kov(cur->_data))
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				//这里实现那种不能重复插入的类型，如果相同直接退出插入
				return make_pair(iterator(cur), false);
			}
		}
		//到这里cur为空，parent就是空的父节点，直接链接起来就好，但是要注意维护三叉链
		Node* node = new Node(kv);
		node->_cl = Red;
		//到这里无法判断大小，需要重新判断插入
		if (kov(kv) > kov(parent->_data))
		{
			//插入在右边
			parent->_right = node;
			node->_parent = parent;
		}
		else
		{
			//插入在左边
			parent->_left = node;
			node->_parent = parent;
		}
	 
		//这里就需要调节颜色了
		while (parent && parent->_cl==Red)
		{
			Node* grandfather = parent->_parent;
			//	1.		grandfather			2.		grandfather
			//		parent		 uncle			uncle		  parent
			if (grandfather->_left == parent)
			{
				Node* uncle = grandfather->_right;
				//只要进来就一定是两个连着的红节点
				if (uncle && uncle->_cl == Red)
				{
					//这只需要调节颜色就好,当把uncle和parent两个节点变黑之后这两部分路径就会多出来一个黑节点，所以需要将grandfather给变红
					//以此来抵消多出来的黑节点
					uncle->_cl = Black;
					parent->_cl = Black;
					grandfather->_cl = Red;
					//向上迭代
					node = grandfather;
					parent = node->_parent;
				}
				else//uncle不存在，或者存在且为黑
				{
					if (parent->_left == node)
					{
						RotateR(grandfather);
						grandfather->_cl = Red;
						parent->_cl = Black;
					}
					else//第二种情况
					{
						RotateL(parent);
						RotateR(grandfather);
						node->_cl = Black;
						grandfather->_cl = Red;
					}
					break;
				}
			}
			else//情况反过来，grandfather->_right == parent
			{
				Node* uncle = grandfather->_left;
				if (uncle && uncle->_cl == Red)
				{
					uncle->_cl = Black;
					parent->_cl = Black;
					grandfather->_cl = Red;
					node = grandfather;
					parent = node->_parent;
				}
				else//uncle不存在，或者存在且为黑
				{
					if (parent->_right == node)//第一种情况
					{
						RotateL(grandfather);
						grandfather->_cl = Red;
						parent->_cl = Black;
					}
					else//第二种情况
					{
						RotateR(parent);
						RotateL(grandfather);
						node->_cl = Black;
						grandfather->_cl = Red;
					}
					break;
				}
			}
		}
		_root->_cl = Black;
		return make_pair(iterator(node), true);
	}
	bool IsBalance()
	{
		if (_root && _root->_cl == Red)
		{
			cout << "根节点是红色不为黑" << endl;
			return false;
		}
		int benchmark = 0;
		Node* left = _root;
		while (left)
		{
			if (left->_cl == Black)
				++benchmark;
			left = left->_left;
		}
		int blacknum = 0;
		return _IsBalance(_root, blacknum, benchmark);
	}
	int Height()
	{
		return _Height(_root);
	}
	int _Height(Node* root)
	{
		if (root == NULL)
			return 0;
		int leftHeight = _Height(root->_left);
		int rightHeight = _Height(root->_right);
		return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
	}
	void InOrder()
	{
		_InOrder(_root);
	}
	~RBTree()
	{
		Destroy(_root);
		_root = nullptr;
	}
protected:
	/*RBTreeNode<T>* _left;
	RBTreeNode<T>* _right;
	RBTreeNode<T>* _parent;
	T _data;
	Colour _cl;*/
	void Destroy(Node* root)
	{
		if (root == nullptr)
			return;
		Destroy(root->_left);
		Destroy(root->_right);
		delete root;
	}
	Node* Copy(Node* root)
	{
		//颜色，值都可以拷贝，但是三叉链不可以，需要自己重新链接
		//首先是判断root
		if (root == nullptr)
			return nullptr;
		Node* newNode = new Node(root->_data);
		newNode->_cl = root->_cl;
		newNode->_left = Copy(root->_left);
		newNode->_right = Copy(root->_right);
		//newNode虽然不知道他的父亲是谁，但是newNode的孩子的父亲是newNode
		if (newNode->_left)
			newNode->_left->_parent = newNode;
		if (newNode->_right)
			newNode->_right->_parent = newNode;
		return newNode;
	}
	void _InOrder(Node* root)
	{
		if (root == nullptr)
			return;

		_InOrder(root->_left);
		cout << root->_data.first << ":" << root->_data.second << endl;
		_InOrder(root->_right);
	}
	bool _IsBalance(Node* root, int blacknum, int benchmark)
	{
		if (root == nullptr)
		{
			if (blacknum != benchmark)
			{
				cout << "黑节点个数不相符" << endl;
				return false;
			}
			return true;
		}
		if (root->_cl == Red && root->_parent->_cl == Red)
		{
			cout << "有两个连续的红节点" << endl;
			return false;
		}
		if (root->_cl == Black)
		{
			++blacknum;
		}
		return	_IsBalance(root->_left, blacknum, benchmark)
			&& _IsBalance(root->_right, blacknum, benchmark);
	}
	void RotateR(Node* parent)
	{
		//右单旋肯定是左树高，右树低
		//旋法就是：把subL的右树给给parent当左树，然后将subL当做新的父节点，将parent接在subL的右边
		//要注意如果parent是根节点，那么就需要更新_root，如果不是根节点，则只需要将subL的parent指向parent的parent
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;
		subL->_right = parent;
		Node* Parentparent = parent->_parent;
		parent->_parent = subL;
		if (parent == _root)
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		else
		{
			subL->_parent = Parentparent;
			if (Parentparent->_right == parent)
				Parentparent->_right = subL;
			else
				Parentparent->_left = subL;
		}
	}
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;
		subR->_left = parent;
		Node* Parentparent = parent->_parent;
		parent->_parent = subR;
		if (parent == _root)
		{
			_root = subR;
			subR->_parent = nullptr;
		}
		else
		{
			subR->_parent = Parentparent;
			if (Parentparent->_left == parent)
				Parentparent->_left = subR;
			else
				Parentparent->_right = subR;
		}
	}
private:
	Node* _root;
};
