#include<iostream>
using namespace std;
//extern可以让c++文件跑c的文件，让c可以跑c++的文件
// 就是相当于extern告诉了编译器extern"C"{}里面的函数是用C的编译方式编译的，链接的时候用C的函数名编译规则去找
//具体用法就是如下：(c++跑c的文件)
extern "C"
{
	// ..是返回上一级文件是从本代码的储存位置向上返回 /就是进入文件
	#include"../../../C-first_stage-/12_1/Stack/Stack/Stack.h"
	//光包头文件是不行的
	//首先打开解决方案资源管理器，右击项目选择属性进行设置  链接器-->常规-->添加附加库目录(将含有静态库文件的Debug地址输入进去)：E:\github\C-first_stage-\12_1\Stack\Debug
	//然后就是继续  链接器-->输入-->附加依赖项  ：在里面输入静态库的名称在结尾加上 ;  例如这个例子就是加入 Stack.lib;
	//这样就能够运行了
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