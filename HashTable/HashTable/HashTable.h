#pragma once
//��ϣ����STL��Ҳ��Ӧ�ã����д���ľ���unordered_map��unordered_set
//ͨ��֮ǰ��ѧϰ����֪��map��set�ĵײ���һ�ú������ʵ�ֵģ���unordered_map��unordered_set�ĵײ���ͨ����ϣ����ʵ�ֵ�
//unordered������ģ���ϣ������ʵ����һ��ӳ���ϵ�ı�֮ǰ�ļ��������õľ������֣���int���͵������������ӣ��洢����ʱ
//���Ը�Ҫ�������ȡģ��ȷ��λ�ã�����ͱ��ⲻ�˻������ͻ��Ҳ���Ƕ�����ݻᶨλ����ͬ��λ�ã��������ϣ��ͻ
//�����ϣ��ͻ��������Ϊ�����ķ�ʽ:��ɢ��(���Ŷ�ַ��)�Ϳ�ɢ��
//��ɢ�� --->����̽��Ͷ���̽�� 
// ����̽�⣺�ӷ�����ͻ��λ�ÿ�ʼ���������̽�⣬ֱ��Ѱ�ҵ���һ����λ��Ϊֹ
// ����̽��ȱ�㣺һ��������ϣ��ͻ�����еĳ�ͻ����һ�����ײ������ݡ��ѻ���
// ������ͬ�ؼ���ռ�ݿ����õĿ�λ�ã�ʹ��Ѱ��ĳ�ؼ����λ����Ҫ���αȽϣ���������Ч�ʽ���
// ����̽���ȱ���ǲ�����ͻ�����ݶѻ���һ�飬����������һ����λ���й�ϵ����Ϊ�ҿ�λ�õķ�ʽ����
//����̽�⣺�����������ȥ�ң���˶���̽��Ϊ�˱�������⣬����һ����λ�õķ���Ϊ�� Hi= (H0+i*i) % m,
//���ߣ�Hi= (H0-i*i) % m�����У�i = 1, 2, 3���� ��ͨ��ɢ�к���Hash(x)��Ԫ�صĹؼ��� key ���м���õ���λ�ã�m�Ǳ�Ĵ�С��
//��������ϣ��ͻʱ�������ϣ��δ��װ����˵���ڹ�ϣ���б�Ȼ���п�λ�ã���ô���԰�key��ŵ���ͻλ���еġ���һ���� ��λ����ȥ��


//��һ�����⣺ ��map/set��key��ʲôҪ��unordered_map/unordered_set����ʲôҪ��
//ǰ���:��ҪKey֧�ֽϴ�С����֧�ֱȽϴ�С�ķº���
//�����:��ҪKey�ܹ�ת�����޷��ŵ����ͣ�����֧��Keyת�����޷������͵ķº���

//��������������ռ䶼Ҫ�õ������Ծͷ���������
//����ֻ��Key��Value�Ļ��������string���͵Ļ�����������صĹ�ϣ��ͻ
//��Ϊstring�ıȽ��ǱȽ��׸���ĸ�Ĵ�С���������Ǿ���Ҫ�õ��º���
template<class Key>
struct Hash
{
	//����HashFunc()����key
	size_t operator()(const Key& k)
	{
		return k;
	}
};
//ģ����ػ�
template<>
struct Hash<string>
{
	size_t operator()(const string& s)
	{
		// BKDR
		//ÿһ����ĸ����31������ӣ�JAVA�õľ��������㷨
		size_t value = 0;
		for (auto ch : s)
		{
			value *= 31;
			value += ch;
		}
		return value;
	}
};
//��ɢ��
namespace  ClosedHash
{
	enum State
	{
		EMPTY, //Ϊ��
		EXIST,//����
		DELETE //ɾ��
	};
	template<class Key,class Value>
	struct HashData
	{
		HashData()
			:_st(EMPTY)
		{}
		//��ǰ�ڵ��״̬
		State _st;
		pair<Key, Value> _pa;
	};
	//��ϣ���ṩһ���º����ӿڣ���������������Զ������ͣ�ֻ��Ҫ���Զ���������Ӧ�ķº�������
	template<class Key,class Value,class HashFunc = Hash<Key>>
	class HashTable
	{
		typedef HashData<Key, Value> HashData;
	public:
		HashTable()
			:_size(0)
		{}
		HashData* find(const Key& k)
		{
			HashFunc hf;
			if (_hd.size() == 0)
				return nullptr;
			int start = hf(k)% _hd.size();
			int i = 0;
			int index = start;
			//�����ڵ�ʱ��ȥ�Ƚ���û��key��ͬ�ģ����������ͬ����״̬�Ѿ���Ϊ�����ˣ���ô���Ǳ�����û��
			while (_hd[index]._st == EXIST)
			{
				if (hf(_hd[index]._pa.first) == hf(k))
				{
					return &_hd[index];
				}
				++i;
				index = (index + i*i) % _hd.size();
			}
			return nullptr;
		}
		bool insert(const pair<Key, Value>& pa)
		{
			//�������ֱ�ӷ���false
			HashData* ret = find(pa.first);
			if (ret)
				return false;
			//����vector��Ҫ����ռ���ܹ����к�������������resize��ֱ�Ӿͳ�ʼ������ʹ����
			//�������ӵļ�������� �洢������/size Ϊʲô������capacity�أ���Ϊ�п���ʹ�õĿռ�δ����ʼ�������ʻ��������
			//�������������趨���ܳ���0.7����ͻ��Զ�����
			if (_hd.size() == 0 || _size * 10 / _hd.size() >= 7)
			{
				int newsize = (_hd.size() == 0 ? 10 : 2 * _hd.size());
				HashTable<Key, Value> newhash;
				newhash._hd.resize(newsize);
				for (size_t i = 0; i < _hd.size(); ++i)
				{
					if (_hd[i]._st == EXIST)
					{
						newhash.insert(_hd[i]._pa);
					}
				}
				//vector�Դ���swap
				_hd.swap(newhash._hd);
			}
			//����̽��or����̽��
			HashFunc hf;
			int start = hf(pa.first) % _hd.size();
			//int i = 1;
			int i = 0;
			int index = start;
			while (_hd[index]._st == EXIST)
			{
				//��i=1��Ȼ��indexÿ��ѭ��������i���������̽�⣬���i����++��index+i���Ƕ���̽��
				++i;
				index = (index + i) % _hd.size();
			}
			_hd[index]._pa = pa;
			_hd[index]._st = EXIST;
			++_size;
			return true;
		}
		bool erase(const Key& k)
		{
			HashData* ret = find(k);
			if (ret)
			{
				//αɾ����
				ret->_st = DELETE;
				--_size;
				return true;
			}
			return false;
		}
	private:
		vector<HashData> _hd;
		//�洢����Ч����
		int _size;
	};
}
namespace LinkHash 
{
	//��ʽ��ϣҲ���ǹ�ϣͰ
	enum State
	{
		EXIST,//����
		EMPTY, //Ϊ��
		DELETE //ɾ��
	};
	template<class Key, class Value>
	struct HashData
	{
		HashData(const pair<Key, Value>& kv)
			:_kv(kv)
			,_next(nullptr)
		{}
		pair<Key, Value> _kv;
		//�����һ��forward_list
		HashData<Key, Value>* _next;
	};
	//defaultĬ�� C++11��һ���﷨����ǿ�Ʊ�����ʵ��һ���޲εĹ��� HashTable() = default;
	template<class Key,class Value,class HashFunc = Hash<Key>>
	class HashTable
	{
		typedef HashData<Key, Value> HashData;
	public:
		HashTable()
			:_size(0)
		{}
		HashData* find(const Key& k)
		{
			if (_table.empty())
				return nullptr;
			HashFunc hf;
			size_t index = hf(k) % _table.size();
			HashData* cur = _table[index];
			while (cur)
			{
				if (cur->_kv.first == k)
				{
					return cur;
				}
				else
				{
					cur = cur->_next;
				}
			}
			return nullptr;
		}
		bool Insert(const pair<Key,Value>& pa)
		{
			HashData* ret = find(pa.first);
			if (ret)
				return false;
			HashFunc hf;
			if (_size == _table.size())
			{
				size_t newsize = (_table.size() == 0 ? 10 : _table.size() * 2);
				vector<HashData*> newhd;
				newhd.resize(newsize);
				//����Ļ������ҿ�ͰȻ��һ��һ����ͷ�壬�������ͷ��Ч�ʸ�
				for (int i = 0; i < _size; ++i)
				{
					//�Ҳ�Ϊ�յ�Ͱ
					HashData* cur = _table[i];
					while (cur)
					{
						//����ӳ��λ��Ȼ��ͷ��
						size_t index = hf(cur->_kv.first) % newhd.size();
						HashData* next = cur->_next;
						cur->_next = newhd[index];
						newhd[index] = cur;
						cur = next;
					}
					//���������˾��ÿ�
					_table[i] = nullptr;
				}
				_table.swap(newhd);
			}
			//�����ݿ�ʼ����
			size_t index = hf(pa.first) % _table.size();
			HashData* next = _table[index];
			HashData* data = new HashData(pa);
			_table[index] = data;
			data->_next = next;
			++_size;
			return true;
		}
		bool Erase(const Key& k)
		{
			if(_table.empty())
				return false;
			HashFunc hf;
			size_t index = hf(k) % _table.size();
			HashData* cur = _table[index];
			while (cur)
			{
				HashData* prev = nullptr;
				if (cur->_kv.first == k)
				{
					if (prev == nullptr)//Ͱͷ����Ҫɾ��
						_table[index] = cur->_next;
					else //ɾ�м�
						prev->_next = cur->_next;
					--_size;
					delete cur;
					return true;
				}
				else
				{
					prev = cur;
					cur = cur->_next;
				}
			}
			return false;
		}
	private:
		vector<HashData*> _table;
		//��Ÿ���������ƽ������ʱ�����ǿ���ѡ������������vector���Ŀռ��ʱ���ڽ�������
		//���ƽ�������Ļ�����һ��Ͱ�����һ��
		int _size;
	};
}