#pragma once
//�����
//1.���ڵ����ɫ�����Ǻ�ɫ
//2.��ڵ�ĺ��ӱ����Ǻ�ɫ
//3.����ÿ����㣬�Ӹý�㵽�����к��Ҷ���ļ�·���ϣ���������ͬ��Ŀ�ĺ�ɫ���  ������Ա�֤�·���еĽڵ㲻�ᳬ�����·��������
//������������·������ȫ��n�����·������һ��һ��Ҳ����2n
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
		//�������Ҫ�ƻ�������Ľṹ�����ƻ���һ�����������أ����ǵڶ�����Ҳ���ǲ����ڵ�
		//��Ϊ����ǵ�����������ڽڵ�Ļ��Ķ��ľͲ�ֻ��һ��·���ˣ�����·�������յ�Ӱ��
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
			//�������Ĵ���_root�������Ǿ����ұ߲���
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
				//����ʵ�����ֲ����ظ���������ͣ������ֱͬ���˳�����
				return false;
			}
		}
		//������curΪ�գ�parent���ǿյĸ��ڵ㣬ֱ�����������ͺã�����Ҫע��ά��������
		Node* node = new Node(kv);
		node->_cl = Red;
		//�������޷��жϴ�С����Ҫ�����жϲ���
		if (kv.first > parent->_kv.first)
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
					//���������������parent,grandfather,node����һ�����ϺͲ���һ������Ҳ����
					//	1.			grandfather             2.       grandfather
					//			parent		  uncle				parent			uncle
					//		node									  node
					if (parent->_left == node)//��һ�����
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
					//���������������parent,grandfather,node����һ�����ϺͲ���һ������Ҳ����
					//	1.			grandfather             2.			grandfather
					//			uncle		parent		  			uncle		   parent
					//							  node								     node
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
			cout << "���ڵ��Ǻ�ɫ��Ϊ��" << endl;
			return false;
		}
		//�Ƚ�һ��·���ĺڽڵ������Ϊ��׼����Ϊÿ��·������ĺڽڵ㶼��Ҫ��ͬ
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
