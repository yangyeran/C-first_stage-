#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
    int W = 0, H = 0;
    scanf("%d %d", &W, &H);
    //W��     H��
    int** arr = (int**)malloc(sizeof(int*) * W);
    for (int i = 0; i < W; i++)
    {
        arr[i] = (int*)malloc(sizeof(int) * H);
    }
    //����һ����ά���飬���Ұ������ֵ����ֵΪ1
    //˼·���ȴӵ�һ����ʼ�ŵ������������в����ʵľͽ����������ֵ��Ϊ0��Ȼ�������������һ�黹Ϊ1��count++
    for (int i = 0; i < W; i++)
    {
        for (int j = 0; j < H; j++)
        {
            arr[i][j] = 1;
        }
    }
    int count = 0;
    for (int i = 0; i < W; i++)
    {
        for (int j = 0; j < H; j++)
        {
            if (arr[i][j] == 1)
            {
                count++;
                //����2�Ķ����ܹ���
                if (i + 2 < W)
                    arr[i + 2][j] = 0;
                if (j + 2 < H)
                    arr[i][j + 2] = 0;
            }
        }
    }
    printf("%d\n", count);
    return 0;
}