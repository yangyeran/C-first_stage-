#pragma once
//����֪��map��set�ĵĵײ㶼�Ǻ����������������Ҫȥ˼����β��ܹ���RBTree�ܹ�ͬʱ֧��<Key,Value>��<Key>ģ����
//���ǿ���ȥ�ٴη�װ�������������
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
	//��֪��������ʲô���ͣ���Ҫ����֮�����֪��
	T _data;
	Colour _cl;
};
template<class T,class Ref,class Ptr>
struct RBTreeIterator
{
	//���ʾ���ָ�룬����Ҫ�洢һ��������Ľڵ�
	typedef RBTreeNode<T> Node;
	typedef RBTreeIterator<T, Ref, Ptr> Self;
	Node* _node;
	RBTreeIterator(Node* node)
		:_node(node)
	{}
	Self& operator++() 
	{
		//��ΪRBTree������ģ�����++һ�����ԭ�ȵĴ�����Ϊ���ʵ������ΪС����Ϊ��
		//����ֻ�������ߣ���ô���м������
		//1���Ҳ�Ϊ��
		if (_node->_right)
		{
			Node* pNode = _node->_right;
			//����ұ߽ڵ�������������ô��ȥ��������ȥ��,���û������������pNode
			while (pNode->_left)
			{
				pNode = pNode->_left;
			}
			_node = pNode;
		}
		//2����Ϊ���Ǿ�ȥ������ȥ�ң����ܲ�ֻ����һ��
		else
		{
			Node* cur = _node;
			Node* parent = _node->_parent;
			//�����ڵ������������cur��parent����Ҳ�����
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
		//�����������Ϊ��
		if (_node->_left)
		{
			Node* pNode = _node->_left;
			while (pNode->_right)
			{
				pNode = pNode->_right;
			}
			_node = pNode;
		}
		//���Ϊ��
		else
		{
			Node* cur = _node;
			Node* parent = cur->_parent;
			//������ײ����ڻ��ߵ�cur�Ǹ��׵���ʱ����
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
	//������ĵ�������ֻ��Ҫ�Ƚϱ����Ƿ���ͬ��������ֵ
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
	//��������
	RBTree(const RBTree<Key,Value,KeyofValue>& rbt)
	{
		_root = Copy(rbt._root);
	}
	//��ֵ����
	RBTree<Key, Value, KeyofValue>& operator=(RBTree<Key, Value, KeyofValue> rbt)
	{
		swap(_root, rbt._root);
		return *this;
	}
	//���ص��ǵ�����
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
		//����ڵ㼴ʹbegin
		Node* min = _root;
		while (min && min->_left)
		{
			min = min->_left;
		}
		return iterator(min);
	}
	//���ص������һ���ڵ�ĺ�һ���ڵ㣬����ʵ�ֲ�û���ڱ�λ��ͷ���
	//���Կ���ֱ�ӷ���nullptr
	iterator end()
	{
		return iterator(nullptr);
	}
	//Value�Ǹ���ȷ�������ͣ���֪����map���û���set����
	//�������Ҫ�õ��º�����
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
			//�º�������ģ�������ʱ�򴫵������ͣ����õ�ʱ�򴫵��Ƕ���
			//�������Ĵ���_root�������Ǿ����ұ߲���
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
				//����ʵ�����ֲ����ظ���������ͣ������ֱͬ���˳�����
				return make_pair(iterator(cur), false);
			}
		}
		//������curΪ�գ�parent���ǿյĸ��ڵ㣬ֱ�����������ͺã�����Ҫע��ά��������
		Node* node = new Node(kv);
		node->_cl = Red;
		//�������޷��жϴ�С����Ҫ�����жϲ���
		if (kov(kv) > kov(parent->_data))
		{
			//�������ұ�
			parent->_right = node;
			node->_parent = parent;
		}
		else
		{
			//���������
			parent->_left = node;
			node->_parent = parent;
		}
	 
		//�������Ҫ������ɫ��
		while (parent && parent->_cl==Red)
		{
			Node* grandfather = parent->_parent;
			//	1.		grandfather			2.		grandfather
			//		parent		 uncle			uncle		  parent
			if (grandfather->_left == parent)
			{
				Node* uncle = grandfather->_right;
				//ֻҪ������һ�����������ŵĺ�ڵ�
				if (uncle && uncle->_cl == Red)
				{
					//��ֻ��Ҫ������ɫ�ͺ�,����uncle��parent�����ڵ���֮����������·���ͻ�����һ���ڽڵ㣬������Ҫ��grandfather�����
					//�Դ�������������ĺڽڵ�
					uncle->_cl = Black;
					parent->_cl = Black;
					grandfather->_cl = Red;
					//���ϵ���
					node = grandfather;
					parent = node->_parent;
				}
				else//uncle�����ڣ����ߴ�����Ϊ��
				{
					if (parent->_left == node)
					{
						RotateR(grandfather);
						grandfather->_cl = Red;
						parent->_cl = Black;
					}
					else//�ڶ������
					{
						RotateL(parent);
						RotateR(grandfather);
						node->_cl = Black;
						grandfather->_cl = Red;
					}
					break;
				}
			}
			else//�����������grandfather->_right == parent
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
				else//uncle�����ڣ����ߴ�����Ϊ��
				{
					if (parent->_right == node)//��һ�����
					{
						RotateL(grandfather);
						grandfather->_cl = Red;
						parent->_cl = Black;
					}
					else//�ڶ������
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
			cout << "���ڵ��Ǻ�ɫ��Ϊ��" << endl;
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
		//��ɫ��ֵ�����Կ��������������������ԣ���Ҫ�Լ���������
		//�������ж�root
		if (root == nullptr)
			return nullptr;
		Node* newNode = new Node(root->_data);
		newNode->_cl = root->_cl;
		newNode->_left = Copy(root->_left);
		newNode->_right = Copy(root->_right);
		//newNode��Ȼ��֪�����ĸ�����˭������newNode�ĺ��ӵĸ�����newNode
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
				cout << "�ڽڵ���������" << endl;
				return false;
			}
			return true;
		}
		if (root->_cl == Red && root->_parent->_cl == Red)
		{
			cout << "�����������ĺ�ڵ�" << endl;
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
		//�ҵ����϶��������ߣ�������
		//�������ǣ���subL����������parent��������Ȼ��subL�����µĸ��ڵ㣬��parent����subL���ұ�
		//Ҫע�����parent�Ǹ��ڵ㣬��ô����Ҫ����_root��������Ǹ��ڵ㣬��ֻ��Ҫ��subL��parentָ��parent��parent
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
