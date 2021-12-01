#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
typedef int STDataType;
typedef struct Stack
{
	STDataType* a;
	int top;
	int capacity;
}Stack;
//如果想用c去调用c++的库那就在c++里面加入extern
//因为c是不认识extern的所以需要在c++文件里进行预编译
#ifdef __cplusplus
extern "C"
{
#endif
	void StackInit(Stack* ps);
	void StackDestroy(Stack* ps);
	void StackPush(Stack* ps, STDataType x);
	void StackPop(Stack* ps);
	STDataType StackTop(Stack* ps);
	int StackSize(Stack* ps);
	bool StackEmpty(Stack* ps);
#ifdef __cplusplus
}
#endif