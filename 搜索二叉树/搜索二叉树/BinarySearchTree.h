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
//������һ���Ӧ�ó���������ģ��
//keyģ��---Ҳ�����ڲ���
template<class K>
class BSTree
{
	typedef BSTreeNode<K> Node;
public:
	BSTree()
		:_root(nullptr)
	{}
	//����Ԫ��
	bool insert(const K& key)
	{
		Node* cur = _root;
		Node* parent = nullptr;
		if (_root == nullptr)
		{
			_root = new Node(key);
			return true;
		}
		//Ҫ�ߵ��ղ��ܲ�
		//������ұߣ�С�������
		//��������������ȥ�أ������������С��������
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
				//���ֱ�ӷ��ز�����
				return false;
			}
		}
		//�ߵ�����Ϊ��
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
	//����
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
	//��Ϊ��װ��Ե��root���ܹ��������ʣ����޷������ڵ㣬������Ϊ��������ݹ�ʵ���ֱ��봫��
	//��ô�����и��������������������(Ҳ����ʵ��һ�����������Ӻ��������������)����������
	void Medium_Order()
	{
		_Medium_Order(_root);
	}
	//ɾ��Ԫ��
	//����д����ʵ�֣�Ҫ���������
	//1.��ɾ��Ԫ����Ҷ�ӽڵ�ʱ--->��¼���ڵ�Ȼ��ɾ���ͺ���
	//2.��ɾ��Ԫ��ֻ��һ������ʱ-->��¼���ڵ�Ȼ�󽫱�ɾ���ڵ�ĺ����й¸����ڵ㣬ͬʱ��Ҫ����
	// :��1�����ֻ�����ӣ���ô��Ҫ�й¸����׵����ӣ�2�����ֻ���Һ��ӣ���ô���й¸����׵��Һ���
	// �ɴ�1��2����������Ժϲ����ۣ���ΪҶ�ӽڵ�ָ������Һ��Ӷ�Ϊ�գ�ɾ���ڵ�֮����ָ��Ľڵ�Ҳ��Ҫ�ÿ�
	//3.��ɾ��Ԫ������������ʱ�����ֱ��ɾ���ǲ�����ģ�����ͨ�������ķ�ʽ��ɾ����Ҳ�����ҵ��Ƚ�������ֵ����ʹ����ȥҲ����ı�
	//�����������Ľṹ��Ҳ���ǿ��������ӵ����ҽڵ㣬Ҳ�������Һ��ӵ�����ڵ�(�����ϸ�ڻ���Ҫ���ݴ�����չʾ)
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
			else//�ҵ���
			{
				if (cur->_left == nullptr)
				{
					//�п��ܸ��ڵ�Ϊ�գ�Ҳ����Ҫɾ��ǡ�ɾ��Ǹ��ڵ�
					//Ȼ������������ж�������cur���Ϊ�գ�Ҳ�ʹ�����ڵ����Ϊ�գ�ֱ������Ȼ��ɾ��cur����
					if (parent == nullptr)
						_root = _root->_right;
					else
					{
						if (parent->_left == cur)//����Ǹ��׵��������й�Ҳ���й���������
							parent->_left = cur->_right;
						else//��������
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
						else//��������
							parent->_right = cur->_left;
					}
					delete cur;
				}
				else//���߶���Ϊ��
				{
					//�����ʵ��ѡ���Һ��ӵ�����ڵ�
					Node* Rightmin = cur;//���Ϊʲô������nullptr--->��Ϊ�п���ɾ����Ԫ�ؾ�����С�ڵ�(����û���������ˣ�ȫ��������)�Ͳ�����������ѭ��
					Node* min = cur->_right;
					while (min->_left)
					{
						Rightmin = min;
						min = min->_left;
					}
					//���ǻ��߽������У������׵ݹ�ɾ������Ϊ�Ѿ��������������ṹ��
					cur->_key = min->_key;
					//�����и���Ҫע��ĵ㣬minֻ����С�����������ǲ�������min��Ҷ�ӽڵ㣬���Ի�����Ҫ�й�
					//����Ҫ���ǵ�ɾ��Ԫ������С�ڵ������Ҳ����Rightmin->right==min
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
	//�ݹ����
	bool InsertR(const K& key)
	{
		//��Ϊ�ǵݹ���Ҫ��_root������_root�Ǳ�private���εģ������治�ܹ�����
		//���ǿ���ͨ��ʵ��һ���Ӻ������������޷����ʵ�����
		return _InsertR(_root, key);
	}
	//�ݹ�ɾ��������ݹ�ɾ������򵥣����Ǹ��Ƽ�����ʵ�֣���Ϊ����������ͻᵼ��ջ���
	bool EraseR(const K& key)
	{
		return _EraseR(_root, key);
	}
private:
	//������װһЩ�Ӻ�������������ʹ������ӵ�����
	//�ݹ�ʵ��ɾ�����Ӻ�����ͬ����Ҫ����
	bool _EraseR(Node*& _root, const K& key)
	{
		if (_root == nullptr)
			return false;
		if (_root->_key < key)
			return _EraseR(_root->_right, key);
		else if (_root->_key > key)
			return _EraseR(_root->_left, key);
		else//�ҵ���
		{
			Node* cur = _root;
			if (_root->_left == nullptr)
				_root = _root->_right;
			else if (_root->_right == nullptr)
				_root = _root->_left;
			else//������root���߶���Ϊ��
			{
				//�����������������ҽڵ��
				Node* max = _root->_left;
				while (max->_right)
				{
					max = max->_right;
				}
				swap(_root->_key, max->_key);
				//���������һ��ȥ�ң������и�������ķ���
				//�������ֱ��д�ݹ������⣬��ɾ�����Σ�������Ҫֱ��return
				return _EraseR(_root->_left, key);
			}
			delete cur;
			return true;
		}
	}
	//�ݹ������Ӻ���
	bool _InsertR(Node*& _root, const K& key)
	{
		//���ﴫ���÷ǳ����ŵ�����ͼ����֪����������һ�εĵݹ�ʱ����_root���������
		if (_root == nullptr)
		{
			_root = new Node(key);
			return true;
		}
		else if (_root->_key < key)
			return _InsertR(_root->_right, key);
		else if (_root->_key > key)
			return _InsertR(_root->_left, key);
		else//��Ȳ���ʧ��
			return false;
	}
	//����������Ӻ���
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
	//key/valueģ��--����
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
	//���԰�key���Ϊ��������ݶ�value����Ҫ���ҵ�����
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
		//����������Ӻ���
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