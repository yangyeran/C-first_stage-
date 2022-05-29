#pragma once
//���ȼ����еĵײ�ʵ����ʵ����һ����(heap),����ģ������õ��˷º�����Ĭ��������Ǵ�ѣ�Ҳ���ǴӴ�С����
//������greater��ʱ�򣬻���С������ʵ�ֵĻ�����ֱ��ʹ�ÿ����ṩ��push_heap��pop_heap����������ѡ��
//����ʵ��һ�¶��ŵ����ϵ��������µ���
namespace yyr
{
	template<class T>
	struct less
	{
		bool operator()(const T& x, const T& y) const
		{
			return x < y;
		}
	};
	template<class T>
	struct greater
	{
		bool operator()(const T& x, const T& y) const
		{
			return x > y;
		}
	};
	//����Դ���и���Ĭ��������vector,Compare���Ƿº�����Ĭ����less
	template<class T,class Container = vector<T>,class Compare= less<T>>
	class priority_queue
	{
	private:
		void adjust_up(size_t child)
		{
			Compare com;
			size_t parent = (child - 1) / 2;
			while (child > 0)//�����parent�������������ͱ�����>=0,��������ж�һ��,���������parent>=0�Ͳ���ʹ��size_t
			{
				//if (_con[parent] < _con[child])
				if(com(_con[parent],_con[child]))
				{
					swap(_con[parent], _con[child]);
					child = parent;
					parent = (child - 1) / 2;
				}
				else
				{
					break;
				}
			}
		}
		void adjust_down(size_t parent)
		{
			Compare com;
			size_t child = parent * 2 + 1;//����
			while (child < _con.size())
			{
				//if (child + 1 < _con.size() && _con[child] < _con[child + 1])
				if (child + 1 < _con.size() && com(_con[child],_con[child + 1]))
				{
					++child;
				}

				//if (_con[parent] < _con[child])
				if(com(_con[parent],_con[child]))
				{
					swap(_con[parent], _con[child]);
					parent = child;
					child = parent * 2 + 1;
				}
				else
				{
					break;
				}
			}
		}
	public:
		priority_queue(const Container& val= Container())
			:_con(val)
		{}
		template<class InputIterator>
		priority_queue(InputIterator first,InputIterator last)
			:_con(first,last)//ֱ�ӵ���Ĭ�������ĵ���������
		{
			//Ȼ��ʼʵ�ֽ��Ѳ���
			for (int i = (_con.size() - 1 - 1) / 2; i >= 0; --i)
			{
				adjust_down(i);
			}
		}
		void push(const T& val)
		{
			//��Ϊ��β��Ԫ�أ�������Ҫ����ȥ����
			_con.push_back(val);
			adjust_up(_con.size()-1);
		}
		void pop()
		{
			//���п϶��Ǵ�ͷ��ʼ�����ݣ�����Ϊ�ײ��Ƕѣ�������Ҫ��ͷβԪ�ؽ���
			//Ȼ��ɾ��β��Ԫ�أ�ͬʱ�������µ���
			swap(_con[0], _con[_con.size() - 1]);
			_con.pop_back();
			adjust_down(0);
		}
		const T& top() const
		{
			return _con[0];
		}
		bool empty() const
		{
			return _con.empty();
		}
	private:
		Container _con;
	};
}