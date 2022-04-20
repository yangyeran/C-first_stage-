#pragma once
namespace yyr 
{
	class String
	{
	public:
		//ֻҪ�Լ�ʵ�ֵ�string֧�ֵ������ͻ�֧�ַ�Χfor(ǰ��������Ҫ�淶������Χfor���ǻᱨ��)
		// ��Χfor�����ڱ����ʱ���滻�ɵ�����
		//��������һ��������ָ��һ���Ķ�������string�п��԰������Ϊָ��
		typedef char* iterator;
		typedef const char* const_iterator;
		iterator begin()
		{
			return _str;
		}
		iterator end()
		{
			return _str + _size;
		}
		const_iterator begin() const
		{
			return _str;
		}
		const_iterator end() const
		{
			return _str+_size;
		}
		 void Swap(String& str)
		{
			 //���������Ҫswap()
			std::swap(_str, str._str);
			std::swap(_size, str._size);
			std::swap(_capacity, str._capacity);
		}
		//strlen(str)�������Ч�ַ����ȣ���Ҫ�ټӸ�1
		//String s("hello")
		String(const char* str="")//��Ϊ�������Զ�string������ɾ��ĵ�һϵ�в�����������Ҫ�ڶ��Ͽ��ռ�
			:_size(strlen(str))
			,_capacity(_size)
		{
			_str = new char[_capacity + 1];
			strcpy(_str,str);
		}
		////String s1(s);
		////��ͳд��
		//String(const String& str)
		//	:_size(str._size)
		//	, _capacity(str._capacity)
		//{
		//	_str = new char[_capacity + 1];
		//	strcpy(_str,str._str);
		//}
		////s1=s2
		//String& operator=(const String& str)
		//{
		//	//if (this != &str) {
		//	//	//���ռ�ֻҪ��ַ��ȷ�Ͳ������
		//	//	delete[] _str;
		//	//	//���ǿ��ٿռ䲻һ�������ٿռ�ʧ�ܾͻ����쳣ֱ������ȥ��
		//	//	//��ᵼ�²���û�и�ֵ�ɹ�������ԭ���Ŀռ��ͷ��ˣ����Կ�����һ����ʱ����������
		//	//	_str = new char[strlen(str._str) + 1];
		//	//	strcpy(_str, str._str);
		//	//}
		//	//return *this;
		//	if (this != &str) {
		//		char* temp = new char[str._capacity + 1];
		//		strcpy(temp, str._str);
		//		//���ǰ�濪�ռ�ʧ�����쳣�ˣ��ǲ�������delete��һ����
		//		delete[] _str;
		//		_str = temp;
		//		_size = str._size;
		//		_capacity = str._capacity;
		//	}
		//	return *this;
		//}


		//�ִ�д��----ʵ�ּ򵥵�string(��������ɾ���) ���ʾ��Ǵ���ĸ���
		String(const String& str)
			:_str(nullptr)
			,_size(0)
			,_capacity(0)
		{
			String temp(str._str);
			Swap(temp);
		}
		//String& operator=(const String& str)
		//{
		//	if (this != &str)
		//	{
		//		//s1=s2
		//		//��������ܰѵ�ַ����ȥ�ˣ�����temp���Զ��������������������s1���õĿռ���ͷ���
		//		String temp(str);
		//		swap(_str, temp._str);
		//	}
		//	return *this;
		//}
		String& operator=(String str)
		{
			//s1=s2
			//�βξ���ʵ�ε���ʱ���������������str���൱�������temp
			//���ﲻ���ж��Ƿ����Լ����Լ���ֵ����Ϊstr�Ѿ���s2����ʱ�����ˣ���ַ�Ѿ���һ����
			Swap(str);
			return *this;
		}
		void reserve(size_t n)
		{
			if (n > _capacity)
			{
				char* temp = new char[n+1];//����һ����ʱ���ݴ洢,����ڴ治����ֱ�����쳣
				strcpy(temp, _str);
				delete[] _str;
				_str = temp;
				_capacity = n;//���������Ч�ڴ�
			}
		}
		//resize(5); resize(6,'x');  resize(20,'y')
		void resize(size_t n, char c = '\0')
		{
			if (n > _capacity)
			{
				reserve(n);
				memset(_str+_size,c,n-_size);
			}
			_size = _capacity;
			_str[_size] = '\0';
		}
		size_t find(char c)
		{
			for (size_t i = 0; i < _size; ++i)
			{
				if (_str[i] == c)
				{
					return i;
				}
			}
			return npos;
		}
		size_t find(const char* str, size_t pos = 0)
		{
			char* ret = strstr(_str + pos, str);
			if (ret == nullptr)
			{
				return npos;
			}
			return ret - _str;
		}
		void push_back(char c)
		{
			insert(_size, c);
			//if (_size == _capacity)
			//{
			//	//����---����ÿ��������
			//	reserve(_capacity == 0 ? 4 : _capacity * 2);
			//}
			////β��
			//_str[_size] = c;
			//++_size;
			//_str[_size] = '\0';
		}
		//β��һ���ַ���
		void append(const char* str)
		{
			insert(_size, str);
			/*size_t len = strlen(str);
			if (len + _size > _capacity)
			{
				reserve(len+_size);
			}
			strcpy(_str+_size, str);
			_size += len;*/
		}
		String& operator+=(const char* str)
		{
			append(str);
			return *this;
		}
		String& operator+=(char c)
		{
			push_back(c);
			return *this;
		}
		void clear()
		{
			//����ַ������ǲ��ı��ڴ�
			_size = 0;
			_str[_size] = '\0';
		}
		const char* c_str() const
		{
			return _str;
		}
		size_t size() const
		{
			return _size;
		}
		size_t capacity() const
		{
			return _capacity;
		}
		bool empty()const
		{
			//�ж��ַ����Ƿ�Ϊ�գ��շ���true�ǿ�false
			if (_size == 0)
				return true;
			return false;
		}
		char& operator[](size_t pos)
		{
			assert(pos < _size);
			return _str[pos];
		}
		const char& operator[](size_t pos) const
		{
			assert(pos < _size);
			return _str[pos];
		}
		String& insert(size_t pos,char c)
		{
			assert(pos<=_size);
			if (_size == _capacity)
			{
				//һ��Ҫע��������String s;
				reserve(_capacity == 0 ? 4 : _capacity * 2);
			}
			size_t end = _size + 1;
			while (end > pos)
			{
				_str[end] = _str[end - 1];
				--end;
			}
			_str[pos] = c;
			++_size;
			return *this;
		}
		String& insert(size_t pos, const char* str)
		{
			assert(pos <= _size);
			size_t len = strlen(str);
			if (len+_size > _capacity)
			{
				reserve(len+_size);
			}
			size_t end = len + _size;
			//�������pos+len����pos�Ļ������Խ�磬end=1ʱ��end-len=-1ת�����޷��ž��Ǻܴ����
			//���ǲ��ᱨ����Ϊֻ�ǿ����ˣ�������ab�����Խ�翽���ĸ�����
			while (end > pos+len)
			{
				_str[end] = _str[end-len];
				--end;
			}
			strncpy(_str+pos,str,len);
			_size += len;
			return *this;
		}
		String& erase(size_t pos = 0, size_t len = npos)
		{
			assert(pos < _size);
			if (len == npos || pos+len >= _size)
			{
				_str[pos] = '\0';
				_size = pos;
			}
			else
			{
				strcpy(_str+pos,_str+len+pos);
				_size -= len;
			}
			return *this;
		}
		~String()
		{
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}
	private:
		char* _str;
		size_t _size;
		size_t _capacity; //����capacity��¼������Ч�ַ�����
		static const size_t npos;
	};
	const size_t String::npos = -1;
}