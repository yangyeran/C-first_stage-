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
//�������cȥ����c++�Ŀ��Ǿ���c++�������extern
//��Ϊc�ǲ���ʶextern��������Ҫ��c++�ļ������Ԥ����
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