#pragma once
/*二叉搜索树虽可以缩短查找的效率，但如果数据有序或接近有序二叉搜索树将退化为单支树，查找元素相当
于在顺序表中搜索元素，效率低下。因此，两位俄罗斯的数学家G.M.Adelson-Velskii和E.M.Landis在1962年
发明了一种解决上述问题的方法：当向二叉搜索树中插入新结点后，如果能保证每个结点的左右子树高度之
差的绝对值不超过1(需要对树中的结点进行调整)，即可降低树的高度，从而减少平均搜索长度。
一棵AVL树或者是空树，或者是具有以下性质的二叉搜索树：
它的左右子树都是AVL树
左右子树高度之差(简称平衡因子)的绝对值不超过1(-1/0/1)*/
template<class Key,class Value>
//定义节点
struct AVLTreeNode
{
	AVLTreeNode<Key,Value>* _left;
	AVLTreeNode<Key,Value>* _right;
	AVLTreeNode<Key,Value>* _parent;
	pair<Key, Value> _kv;
	int _bf; //balance factor平衡因子
	AVLTreeNode(const pair<Key,Value>& kv)
		:_kv(kv)
		, _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		,_bf(0)
	{}
};

template<class Key,class Value>
class AVLTree
{
	typedef AVLTreeNode<Key, Value> Node;
public:
	AVLTree()
		:_root(nullptr)
	{}
	bool Insert(const pair<Key, Value>& kv)
	{
		//AVLTree的插入分为两部分，第一部分是插入，第二部分是旋转
		//插入的方法与二叉搜索树相同
		if (_root == nullptr)
		{
			_root = new Node(kv);
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
		//开始调节平衡因子
		// 1、更新平衡因子 -- 新增节点到根节点的祖先路径
		// 2、出现异常平衡因子，那么需要旋转平衡处理
		while (parent)
		{
			if (parent->_left == node)
				parent->_bf--;
			else
				parent->_bf++;

			//平衡因子只有可能有这几种情况，首先0,1，-1,2，-2
			if (parent->_bf == 0)
			{
				//当节点的平衡因子为0时
				break;
			}
			else if (parent->_bf == 1 || parent->_bf == -1)
			{
				node = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == 2 || parent->_bf == -2)
			{
				//开始旋转
				if (parent->_bf == 2 && node->_bf == 1)
				{
					//平衡因子是2时是左单旋
					RotateL(parent);
				}
				else if (parent->_bf == -2 && node->_bf == -1)//平衡因子是-2时是右单旋
				{
					RotateR(parent);
				}
				else if (parent->_bf == 2 && node->_bf == -1)
				{ 
					RotateRL(parent);
				}
				else if (parent->_bf == -2 && node->_bf == 1)
				{
					RotateLR(parent);
				}
				else
					assert(false);
				break;
			}
			else
			{
				//走到这里表示之前就有问题
				assert(false);
			}
		}
		return true;
	}
	void Inorder()
	{
		_Inorder(_root);
	}
	//查错可以通过高度来进行计算，因为abs(右树-左树)的高度必然是小于2的
	int Height()
	{
		return _Height(_root);
	}
protected:
	int _Height(Node* root)
	{
		if (root == nullptr)
			return 0;
		int lefthight = _Height(root->_left);
		int rightheight = _Height(root->_right);
		if (rightheight - lefthight != root->_bf)
		{
			cout << "_bf应该是：" << rightheight - lefthight << "现在是：" << root->_bf << endl;
		}
		return lefthight > rightheight ? lefthight + 1 : rightheight + 1;
	}
	void _Inorder(const Node* root)
	{
		if (root == nullptr)
			return;
		_Inorder(root->_left);
		cout << root->_kv.first <<" ";
		_Inorder(root->_right);
	}
	void RotateR(Node* parent)
	{
		//右单旋肯定是左树高，右树低
		//旋法就是：把subL的右树给给parent当左树，然后将subL当做新的父节点，将parent接在subL的右边
		//要注意如果parent是根节点，那么就需要更新_root，如果不是根节点，则只需要将subL的parent指向parent的parent
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		parent->_left = subLR;
		//只有右子树不为空的情况下才能去访问
		if(subLR)
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
			//如果不为根就需要考虑，subL是Parentparent的左子树还是右子树,要时刻维护三叉链
			//if (subL->_kv.first > Parentparent->_kv.first)
			if(Parentparent->_right == parent)
				Parentparent->_right = subL;
			else
				Parentparent->_left = subL;
		}
		subL->_bf = parent->_bf = 0;
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
		subR->_bf = parent->_bf = 0;
	}
	void RotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;
		RotateR(parent->_right);
		RotateL(parent);
		if (bf == 1)
		{
			subR->_bf = 0;
			parent->_bf = -1;
			subRL->_bf = 0;
		}
		else if (bf == -1)
		{
			subR->_bf = 1;
			parent->_bf = 0;
			subRL->_bf = 0;
		}
		else if (bf == 0)
		{
			subR->_bf = 0;
			parent->_bf = 0;
			subRL->_bf = 0;
		}
		else
			assert(false);
	}
	void RotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;
		RotateL(parent->_left);
		RotateR(parent);
		if (bf == 1)
		{
			subL->_bf = -1;
			parent->_bf = 0;
			subLR->_bf = 0;
		}
		else if (bf == -1)
		{
			subL->_bf = 0;
			parent->_bf = 1;
			subLR->_bf = 0;
		}
		else if (bf == 0)
		{
			subL->_bf = 0;
			parent->_bf = 0;
			subLR->_bf = 0;
		}
		else
			assert(false);
	}
private:
	Node* _root;
};