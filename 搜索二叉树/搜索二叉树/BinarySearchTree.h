#pragma once
template<class K>
struct BSTreeNode
{
	BSTreeNode(K key)
		:_key(key)
	{
		_left = nullptr;
		_right = nullptr;
	}
	BSTreeNode<K>* _left;
	BSTreeNode<K>* _right;
	K _key;
};
//搜索树一般的应用场景是两种模型
//key模型---也就是在不在
template<class K>
class BSTree
{
	typedef BSTreeNode<K> Node;
public:
	BSTree()
		:_root(nullptr)
	{}
	//插入元素
	bool insert(const K& key)
	{
		Node* cur = _root;
		Node* parent = nullptr;
		if (_root == nullptr)
		{
			_root = new Node(key);
			return true;
		}
		//要走到空才能插
		//大的在右边，小的在左边
		//搜索二叉树天生去重，且中序遍历即小到大排序
		while (cur)
		{
			if (key > cur->_key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (key < cur->_key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				//相等直接返回不插入
				return false;
			}
		}
		//走到这里为空
		cur = new Node(key);
		if (key > parent->_key)
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}
		return true;
	}
	//查找
	bool Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)
			{
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				cur = cur->_left;
			}
			else
			{
				return true;
			}
		}
		return false;
	}
	//因为封装的缘故root不能够被外界访问，就无法传根节点，但是因为中序遍历递归实现又必须传根
	//那么这里有个巧妙的做法，就是套娃(也就是实现一个函数，让子函数在类里面调用)，具体如下
	void Medium_Order()
	{
		_Medium_Order(_root);
	}
	//删除元素
	//首先写迭代实现，要分情况讨论
	//1.当删除元素是叶子节点时--->记录父节点然后删除就好了
	//2.当删除元素只有一个孩子时-->记录父节点然后将被删除节点的孩子托孤给父节点，同时需要考虑
	// :（1）如果只有左孩子，那么需要托孤给父亲的左孩子（2）如果只有右孩子，那么就托孤给父亲的右孩子
	// 由此1和2两种情况可以合并讨论，因为叶子节点指向的左右孩子都为空，删除节点之后父亲指向的节点也需要置空
	//3.当删除元素有两个孩子时，这个直接删除是不方便的，可以通过交换的方式来删除，也就是找到比较中立的值，即使换上去也不会改变
	//搜索二叉树的结构，也就是可以是左孩子的最右节点，也可以是右孩子的最左节点(具体的细节还需要根据代码来展示)
	bool Erase(const K& key)
	{
		if (_root == nullptr)
			return false;
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (key > cur->_key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (key < cur->_key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else//找到了
			{
				if (cur->_left == nullptr)
				{
					//有可能父节点为空，也就是要删的恰巧就是根节点
					//然而根据上面的判断条件，cur左边为空，也就代表根节点左边为空，直接跳过然后删除cur即可
					if (parent == nullptr)
						_root = _root->_right;
					else
					{
						if (parent->_left == cur)//如果是父亲的左子树托孤也是托孤在左子树
							parent->_left = cur->_right;
						else//在右子树
							parent->_right = cur->_right;
					}
					delete cur;
				}
				else if (cur->_right == nullptr)
				{
					if (parent == nullptr)
						_root = _root->_left;
					else
					{
						if (parent->_left == cur)
							parent->_left = cur->_left;
						else//在右子树
							parent->_right = cur->_left;
					}
					delete cur;
				}
				else//两边都不为空
				{
					//这里的实现选择右孩子的最左节点
					Node* Rightmin = cur;//这个为什么不能是nullptr--->因为有可能删除的元素就是最小节点(后面没有左子树了，全是右子树)就不会进入下面的循环
					Node* min = cur->_right;
					while (min->_left)
					{
						Rightmin = min;
						min = min->_left;
					}
					//覆盖或者交换都行，不能套递归删除，因为已经不符合搜索树结构了
					cur->_key = min->_key;
					//这里有个需要注意的点，min只是最小左子树，但是并不代表min是叶子节点，所以还是需要托孤
					//并且要考虑到删除元素是最小节点情况，也就是Rightmin->right==min
					if (Rightmin->_right == min)
						Rightmin->_right = min->_right;
					else
						Rightmin->_left = min->_right;
					delete min;
				}
				return true;
			}
		}
		return false;
	}
	//递归插入
	bool InsertR(const K& key)
	{
		//因为是递归需要传_root，但是_root是被private修饰的，在外面不能够访问
		//我们可以通过实现一个子函数来解决这个无法访问的问题
		return _InsertR(_root, key);
	}
	//递归删除，这里递归删除代码简单，但是更推荐迭代实现，因为数据量过大就会导致栈溢出
	bool EraseR(const K& key)
	{
		return _EraseR(_root, key);
	}
private:
	//用来封装一些子函数，这样可以使代码更加的整洁
	//递归实现删除的子函数，同样需要引用
	bool _EraseR(Node*& _root, const K& key)
	{
		if (_root == nullptr)
			return false;
		if (_root->_key < key)
			return _EraseR(_root->_right, key);
		else if (_root->_key > key)
			return _EraseR(_root->_left, key);
		else//找到了
		{
			Node* cur = _root;
			if (_root->_left == nullptr)
				_root = _root->_right;
			else if (_root->_right == nullptr)
				_root = _root->_left;
			else//这里是root两边都不为空
			{
				//这里找左子树的最右节点吧
				Node* max = _root->_left;
				while (max->_right)
				{
					max = max->_right;
				}
				swap(_root->_key, max->_key);
				//可以像迭代一样去找，但是有个更巧妙的方法
				//下面如果直接写递归会出问题，会删除两次，所以需要直接return
				return _EraseR(_root->_left, key);
			}
			delete cur;
			return true;
		}
	}
	//递归插入的子函数
	bool _InsertR(Node*& _root, const K& key)
	{
		//这里传引用非常有门道，画图可以知道当进行下一次的递归时传的_root就是其别名
		if (_root == nullptr)
		{
			_root = new Node(key);
			return true;
		}
		else if (_root->_key < key)
			return _InsertR(_root->_right, key);
		else if (_root->_key > key)
			return _InsertR(_root->_left, key);
		else//相等插入失败
			return false;
	}
	//中序遍历的子函数
	void _Medium_Order(Node* root)
	{
		if (root == nullptr)
			return;
		_Medium_Order(root->_left);
		cout << root->_key << " ";
		_Medium_Order(root->_right);
	}
private:
	Node* _root;
};
namespace yyr 
{
	//key/value模型--查找
	template<class Key, class Value>
	struct BSTreeNode
	{
		BSTreeNode(Key key, Value value)
			:_key(key)
			, _value(value)
		{
			_left = nullptr;
			_right = nullptr;
		}
		BSTreeNode<Key, Value>* _left;
		BSTreeNode<Key, Value>* _right;
		Key _key;
		Value _value;
	};
	template<class Key, class Value>
	//可以把key理解为插入的数据而value是需要查找的数据
	class BSTree
	{
		typedef BSTreeNode<Key, Value> Node;
	public:
		BSTree()
			:_root(nullptr)
		{}
		bool insert(const Key& key,const Value& value)
		{
			Node* cur = _root;
			Node* parent = nullptr;
			if (_root == nullptr)
			{
				_root = new Node(key,value);
				return true;
			}
			while (cur)
			{
				if (key > cur->_key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else if (key < cur->_key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else
				{
					return false;
				}
			}
			cur = new Node(key,value);
			if (key > parent->_key)
			{
				parent->_right = cur;
			}
			else
			{
				parent->_left = cur;
			}
			return true;
		}
		void Find(const Key& key)
		{
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key < key)
				{
					cur = cur->_right;
				}
				else if (cur->_key > key)
				{
					cur = cur->_left;
				}
				else
				{
					cout << cur->_value << endl;
					return;
				}
			}
			cout << "don't find" << endl;
			return ;
		}
		void Medium_Order()
		{
			_Medium_Order(_root);
		}
		bool Erase(const Key& key)
		{
			if (_root == nullptr)
				return false;
			Node* parent = nullptr;
			Node* cur = _root;
			while (cur)
			{
				if (key > cur->_key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else if (key < cur->_key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else
				{
					if (cur->_left == nullptr)
					{
						if (parent == nullptr)
							_root = _root->_right;
						else
						{
							if (parent->_left == cur)
								parent->_left = cur->_right;
							else
								parent->_right = cur->_right;
						}
						delete cur;
					}
					else if (cur->_right == nullptr)
					{
						if (parent == nullptr)
							_root = _root->_left;
						else
						{
							if (parent->_left == cur)
								parent->_left = cur->_left;
							else
								parent->_right = cur->_left;
						}
						delete cur;
					}
					else
					{
						Node* Rightmin = cur;
						Node* min = cur->_right;
						while (min->_left)
						{
							Rightmin = min;
							min = min->_left;
						}
						cur->_key = min->_key;
						if (Rightmin->_right == min)
							Rightmin->_right = min->_right;
						else
							Rightmin->_left = min->_right;
						delete min;
					}
					return true;
				}
			}
			return false;
		}
	private:
		//中序遍历的子函数
		void _Medium_Order(Node* root)
		{
			if (root == nullptr)
				return;
			_Medium_Order(root->_left);
			cout << root->_key << " ";
			_Medium_Order(root->_right);
		}
	private:
		Node* _root;
	};

}


void fun1()
{
	BSTree<int> bs;
	vector<int> a = { 5,3,4,1,7,8,2,6,9 };
	for (auto e : a)
	{
		bs.insert(e);
	}
	bs.Medium_Order();
}
void fun2()
{
	BSTree<int> bs;
	vector<int> a = { 5,3,4,1,7,8,2,6,9 };
	for (auto e : a)
	{
		bs.insert(e);
	}
	bs.Medium_Order();
	cout << endl;
	bs.Erase(7);
	bs.Medium_Order();
	cout << endl;
	bs.Erase(5);
	bs.Medium_Order();
	cout << endl;
	bs.Erase(1);
	bs.Medium_Order();
	cout << endl;
	bs.Erase(2);
	bs.Medium_Order();
	cout << endl;
	bs.Erase(4);
	bs.Medium_Order();
	cout << endl;
	bs.Erase(3);
	bs.Medium_Order();
	cout << endl;
	bs.Erase(6);
	bs.Medium_Order();
	cout << endl;
	bs.Erase(8);
	bs.Medium_Order();
	cout << endl;
	bs.Erase(9);
	bs.Medium_Order();
	cout << endl;
}
void fun3()
{
	BSTree<int> bs;
	vector<int> a = { 5,3,4,1,7,8,2,6,9 };
	for (auto e : a)
	{
		bs.InsertR(e);
	}
	bs.Medium_Order();
}
void fun4()
{
	BSTree<int> bs;
	vector<int> a = {8,3,12,2,6,1,4,11,13,14};
	for (auto e : a)
	{
		bs.InsertR(e);
	}
	bs.Medium_Order();
	cout << endl;
	bs.EraseR(8);
	bs.Medium_Order();
	cout << endl;
	bs.EraseR(3);
	bs.Medium_Order();
	cout << endl;
	bs.EraseR(12);
	bs.Medium_Order();
	cout << endl;
	bs.EraseR(2);
	bs.Medium_Order();
	cout << endl;
	bs.EraseR(6);
	bs.Medium_Order();
	cout << endl;
	bs.EraseR(1);
	bs.Medium_Order();
	cout << endl;
	bs.EraseR(4);
	bs.Medium_Order();
	cout << endl;
	bs.EraseR(11);
	bs.Medium_Order();
	cout << endl;
	bs.EraseR(13);
	bs.Medium_Order();
	cout << endl;
	bs.EraseR(14);
	bs.Medium_Order();
	cout << endl;
}