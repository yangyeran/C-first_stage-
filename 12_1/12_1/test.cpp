#include<iostream>
using namespace std;
//extern������c++�ļ���c���ļ�����c������c++���ļ�
// �����൱��extern�����˱�����extern"C"{}����ĺ�������C�ı��뷽ʽ����ģ����ӵ�ʱ����C�ĺ������������ȥ��
//�����÷��������£�(c++��c���ļ�)
extern "C"
{
	// ..�Ƿ�����һ���ļ��Ǵӱ�����Ĵ���λ�����Ϸ��� /���ǽ����ļ�
	#include"../../../C-first_stage-/12_1/Stack/Stack/Stack.h"
	//���ͷ�ļ��ǲ��е�
	//���ȴ򿪽��������Դ���������һ���Ŀѡ�����Խ�������  ������-->����-->��Ӹ��ӿ�Ŀ¼(�����о�̬���ļ���Debug��ַ�����ȥ)��E:\github\C-first_stage-\12_1\Stack\Debug
	//Ȼ����Ǽ���  ������-->����-->����������  �����������뾲̬��������ڽ�β���� ;  ����������Ӿ��Ǽ��� Stack.lib;
	//�������ܹ�������
}
void test1()
{
	Stack ST;
	StackInit(&ST);
	StackPush(&ST, 1);
	StackPush(&ST, 2);
	StackPush(&ST, 3);
	StackPush(&ST, 4);
	StackPush(&ST, 5);
	cout<<StackTop(&ST)<<endl;
	StackDestroy(&ST);
}
int main()
{
	test1();
}