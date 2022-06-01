#pragma once
namespace yyr
{
	template<class T,class Container=deque<T>>
	class stack 
	{
	public:
		stack(const Container& tmp=Container())
			:st(tmp)
		{}
		void push(const T& val)
		{
			st.push_back(val);
		}
		void pop()
		{
			st.pop_back();
		}
		T& top()
		{
			return st.back();
		}
		const T& top() const
		{
			return st.back();
		}
		bool empty() const
		{
			return st.empty();
		}
		size_t size() const
		{
			return st.size();
		}
	private:
		Container st;
	};


	//����ʵ�ֵ�queue��֧��û��ͷ�������������vector��������Ҳ�������
	//������ҪƵ����ͷ��ͷɾ�����ʹ��vector��ôʱ�临�ӶȽ���ǳ���
	template<class T, class Container = deque<T>>
	class queue
	{
	public:
		queue(const Container& tmp = Container())
			:qu(tmp)
		{}
		void push(const T& val)
		{
			qu.push_front(val);
		}
		void pop()
		{
			qu.pop_front();
		}
		T& front()
		{
			return qu.front();
		}
		const T& front() const
		{
			return qu.front();
		}
		T& back()
		{
			return qu.back();
		}
		const T& back() const
		{
			return qu.back();
		}
		bool empty() const
		{
			return qu.empty();
		}
		size_t size() const
		{
			return qu.size();
		}
	private:
		Container qu;
	};
}