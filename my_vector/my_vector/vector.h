#pragma once
namespace yyr
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;
		//���캯��
		//1���޲�Ĭ�Ϲ��캯��
		vector()
			:_start(nullptr)
			, _finish(nullptr)
			, _endofstorage(nullptr)
		{}
		//2.���εĹ��캯��
		vector(int n, const T& val = T())//��Ĭ�ϵ���T�Ĺ��캯����������Ҳ�й��캯��int=int(10);
			:_start(nullptr)
			, _finish(nullptr)
			, _endofstorage(nullptr)
		{
			resize(n, val);
		}
		//3.����������
		template<class InputIterator>
		vector(InputIterator first, InputIterator last)
			:_start(nullptr)
			,_finish(nullptr)
			,_endofstorage(nullptr)
		{
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}
		//��������͸�ֵ����
		//v1(v2)-->ʵ����������������ʵ��һ���õ������Ĺ��캯��
		vector(const vector<T>& v)
			:_start(nullptr)
			,_finish(nullptr)
			,_endofstorage(nullptr)
		{
			vector<int> tmp(v.cbegin(),v.cend());
			swap(tmp);
		}
		//��ֵ����
		//v1=v2
		vector<T>& operator=(const vector<T> v)
		{
			swap(v);
			return *this;
		}
		/*vector<T>& operator=(const vector<T>& v)
		{
			vector<T> tmp(v);
			swap(v);
			return *this;
		}*/
		//begin��end
		iterator begin()
		{
			return _start;
		}
		const_iterator cbegin() const
		{
			return _start;
		}
		iterator end()
		{
			return _finish;
		}
		const_iterator cend() const
		{
			return _finish;
		}
		//size
		size_t size() const
		{
			return _finish - _start;
		}
		//empty
		bool empty()
		{
			if (_finish == nullptr)
				return true;
			return false;
		}
		size_t capacity() const
		{
			return _endofstorage-_start;
		}
		T& operator[](size_t n)
		{
			assert(n < size());
			//return start[n];
			return *(_start + n);
		}
		const T& operator[](size_t n) const
		{
			assert(n < size());
			return *(_start + n);
		}
		void swap(vector<T>& v2)
		{
			std::swap(_start, v2._start);
			std::swap(_finish, v2._finish);
			std::swap(_endofstorage, v2._endofstorage);
		}
		void reserve(size_t n)
		{
			if (n > capacity())
			{
				T* temp = new T[n];
				size_t sz = size();
				//for (size_t i = 0; i < size(); ++i)
				//{
				//	temp[i] = _start[i];
				//}
				if (_start)
				{
					//����T���͵�size���ֽ�
					memcpy(temp, _start,sizeof(T)*size());
					delete[] _start;
				}
				_start=temp;
				//��Ҫ��ǰ��size��ֵ����������
				_finish = _start + sz;
				_endofstorage = _start + n;
			}
		}
		void resize(size_t n, const T& val = T())
		{
			//���ռ�+��ʼ��
			if (n < size())
			{
				_finish = _start + n;
			}
			else
			{
				reserve(n);
			}
			//c++�е�vectorʵ���ǲ���ı��Ѿ����ڵ����ݣ��¿��Ŀռ�ᱻ��ʼ��Ϊval
			while (_finish != _endofstorage)
			{
				*_finish = val;
				++_finish;
			}

		}
		//push_back,pop_back,insert,erase
		//push_back
		void push_back(const T& val)
		{
			if (_finish == _endofstorage)
			{
				reserve(capacity()==0?4:capacity()*2);
			}
				*_finish = val;
				++_finish;
		}
		//pop_back
		void pop_back()
		{
			assert(_start<_finish);
			--_finish;
		}
		//����ֵָ���һ���²���Ԫ�صĵ�������
		iterator insert(iterator pos,const T& val)
		{
			//������ʧЧ������Ҫ�����������֮��ԭ���ĵ�ַ�ͻ�ʧЧ
			//����һ�µ������ͺ���
			assert(pos >= _start);
			assert(pos <= _finish);
			if (_finish == _endofstorage)
			{
				//������Ǽ�¼���µ�������
				size_t len = pos - _start;
				reserve(capacity() == 0 ? 4 : capacity() * 2);
				pos = _start + len;
			}
			for (iterator i = end()-1; i >= pos; --i)
			{
				*(i + 1) = *i;
			}
			*pos = val;
			++_finish;
			return pos;
		}
		//����λ��βɾ
		//ָ�������ò��������һ��Ԫ�غ����Ԫ�ص���λ�õĵ�����,ע�ⲻ�ܵ���_finish
		iterator erase(iterator pos)
		{
			assert(pos < _finish);
			assert(pos >= _start);
			for (size_t i = pos - _start; i < capacity(); ++i)
			{
				_start[i] = _start[i + 1];
			}
			--_finish;
			return pos;
		}
		//��������
		~vector()
		{
			delete[] _start;
			_start = _finish = _endofstorage = nullptr;
		}
	private:
		//��ʼ
		iterator _start;
		//���˶�������,ָ��������һ��Ԫ�ص���һ��λ��
		iterator _finish;
		//�ܴ�С
		iterator _endofstorage;
	};
}