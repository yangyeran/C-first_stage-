#pragma once
/*������������������̲��ҵ�Ч�ʣ���������������ӽ�����������������˻�Ϊ��֧��������Ԫ���൱
����˳���������Ԫ�أ�Ч�ʵ��¡���ˣ���λ����˹����ѧ��G.M.Adelson-Velskii��E.M.Landis��1962��
������һ�ֽ����������ķ�������������������в����½�������ܱ�֤ÿ���������������߶�֮
��ľ���ֵ������1(��Ҫ�����еĽ����е���)�����ɽ������ĸ߶ȣ��Ӷ�����ƽ���������ȡ�
һ��AVL�������ǿ����������Ǿ����������ʵĶ�����������
����������������AVL��
���������߶�֮��(���ƽ������)�ľ���ֵ������1(-1/0/1)*/
template<class Key,class Value>
//����ڵ�
struct AVLTreeNode
{
	AVLTreeNode<Key,Value>* _left;
	AVLTreeNode<Key,Value>* _right;
	AVLTreeNode<Key,Value>* _parent;
	pair<Key, Value> _kv;
	int _bf; //balance factorƽ������
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
		//AVLTree�Ĳ����Ϊ�����֣���һ�����ǲ��룬�ڶ���������ת
		//����ķ����������������ͬ
		if (_root == nullptr)
		{
			_root = new Node(kv);
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
		//��ʼ����ƽ������
		// 1������ƽ������ -- �����ڵ㵽���ڵ������·��
		// 2�������쳣ƽ�����ӣ���ô��Ҫ��תƽ�⴦��
		while (parent)
		{
			if (parent->_left == node)
				parent->_bf--;
			else
				parent->_bf++;

			//ƽ������ֻ�п������⼸�����������0,1��-1,2��-2
			if (parent->_bf == 0)
			{
				//���ڵ��ƽ������Ϊ0ʱ
				break;
			}
			else if (parent->_bf == 1 || parent->_bf == -1)
			{
				node = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == 2 || parent->_bf == -2)
			{
				//��ʼ��ת
				if (parent->_bf == 2 && node->_bf == 1)
				{
					//ƽ��������2ʱ������
					RotateL(parent);
				}
				else if (parent->_bf == -2 && node->_bf == -1)//ƽ��������-2ʱ���ҵ���
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
				//�ߵ������ʾ֮ǰ��������
				assert(false);
			}
		}
		return true;
	}
	void Inorder()
	{
		_Inorder(_root);
	}
	//������ͨ���߶������м��㣬��Ϊabs(����-����)�ĸ߶ȱ�Ȼ��С��2��
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
			cout << "_bfӦ���ǣ�" << rightheight - lefthight << "�����ǣ�" << root->_bf << endl;
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
		//�ҵ����϶��������ߣ�������
		//�������ǣ���subL����������parent��������Ȼ��subL�����µĸ��ڵ㣬��parent����subL���ұ�
		//Ҫע�����parent�Ǹ��ڵ㣬��ô����Ҫ����_root��������Ǹ��ڵ㣬��ֻ��Ҫ��subL��parentָ��parent��parent
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		parent->_left = subLR;
		//ֻ����������Ϊ�յ�����²���ȥ����
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
			//�����Ϊ������Ҫ���ǣ�subL��Parentparent������������������,Ҫʱ��ά��������
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