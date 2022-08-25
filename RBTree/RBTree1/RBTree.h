#pragma once
//红黑树
//1.根节点的颜色必须是黑色
//2.红节点的孩子必须是黑色
//3.对于每个结点，从该结点到其所有后代叶结点的简单路径上，均包含相同数目的黑色结点  这个可以保证最长路径中的节点不会超过最短路径的两倍
//极端情况下最短路径就是全黑n，而最长路径就是一红一黑也就是2n
enum Colour
{
	Red,
	Black
};
template<class Key,class Value>
struct RBTreeNode
{
	RBTreeNode(const pair<Key, Value>& kv)
		:_left(nullptr)
		,_right(nullptr)
		,_parent(nullptr)
		,_kv(kv)
	{}
	RBTreeNode<Key,Value>* _left;
	RBTreeNode<Key, Value>* _right;
	RBTreeNode<Key, Value>* _parent;
	pair<Key, Value> _kv;
	Colour _cl;
};
template<class Key, class Value>
class RBTree
{
	typedef RBTreeNode<Key, Value> Node;
public:
	RBTree()
		:_root(nullptr)
	{}
	bool Insert(const pair<Key, Value>& kv)
	{
		//插入就需要破坏红黑树的结构，但破坏哪一个定义会更好呢？答案是第二个，也就是插入红节点
		//因为如果是第三个，插入黑节点的话改动的就不只是一条路径了，其他路径都会收到影响
		if (_root == nullptr)
		{
			_root = new Node(kv);
			_root->_cl = Black;
			return true;
		}
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			//如果插入的大于_root里面存的那就往右边插入
			if (kv.first > cur->_kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (kv.first < cur->_kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				//这里实现那种不能重复插入的类型，如果相同直接退出插入
				return false;
			}
		}
		//到这里cur为空，parent就是空的父节点，直接链接起来就好，但是要注意维护三叉链
		Node* node = new Node(kv);
		node->_cl = Red;
		//到这里无法判断大小，需要重新判断插入
		if (kv.first > parent->_kv.first)
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
					//这又有两种情况，parent,grandfather,node都在一条线上和不在一条线上也就是
					//	1.			grandfather             2.       grandfather
					//			parent		  uncle				parent			uncle
					//		node									  node
					if (parent->_left == node)//第一种情况
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
					//这又有两种情况，parent,grandfather,node都在一条线上和不在一条线上也就是
					//	1.			grandfather             2.			grandfather
					//			uncle		parent		  			uncle		   parent
					//							  node								     node
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
		return true;
	}
	void InOrder()
	{
		_InOrder(_root);
	}
	bool IsBalance()
	{
		if (_root && _root->_cl == Red)
		{
			cout << "根节点是红色不为黑" << endl;
			return false;
		}
		//先将一个路径的黑节点个数作为基准，因为每条路径上面的黑节点都需要相同
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
protected:
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
	void _InOrder(Node* root)
	{
		if (root == nullptr)
			return;

		_InOrder(root->_left);
		cout << root->_kv.first << ":" << root->_kv.second << endl;
		_InOrder(root->_right);
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
