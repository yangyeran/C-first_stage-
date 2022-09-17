#pragma once
//位图是个很巧妙的方法，它的优势就是消耗的空间小查找速率快
//具体做法就是：将40亿个数从文件里面读取出来映射到位图对应的位置，查找的时候输入这个数输出存不存在
//存在返回1，不存在是0，40亿个整型固然很大，但是40亿个bit位就不是那么的大了，大致需要500M左右，这个大小内存是支持的
//具体实现如下：
#include<vector>
namespace MyBitSet
{
	//就是传需要开多大的空间
	template<size_t N>
	class bitset 
	{
	public:
		bitset()
		{
			//char类型的是8个bit，1个bit表示一个数就够了
			_bs.resize(N / 8 + 1, 0);
		}
		//插入元素
		void set(const size_t& k)
		{
			//首先是算法因为是char类型我就定义8个为一组
			//比如10 --> 就是10/8=1,10%8=2-->去第一组的2号去找
			int i = k / 8;
			int j = k % 8;
			//要将对应的j个bit位改为相应的值可以用按位与来，因为0和1与是1,0和0与是0,1和1与是1，不会影响其他位置
			_bs[i] |= (1 << j);
		}
		void reset(const size_t& k)
		{
			//删除对应位置
			int i = k / 8;
			int j = k % 8;
			//只改变对应位置其他位置不变
			// 1<<j --> 如果j==3 --> 0100 
			//                      ~0100 ---> 1011 
			//                       1011& 0101--> 0001只删除了j=3那个位置的1
			_bs[i] &= (~(1 << j));
		}
		bool test(const size_t& k)
		{
			int i = k / 8;
			int j = k % 8;
			//if (_bs[i] & (1 << j) > 0)
			//{
			//	return true;
			//}
			//return false;
			return _bs[i] & (1 << j);
		}
	private:
		vector<char> _bs;
	};
}