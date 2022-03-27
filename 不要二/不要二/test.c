#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
    int W = 0, H = 0;
    scanf("%d %d", &W, &H);
    //W长     H宽
    int** arr = (int**)malloc(sizeof(int*) * W);
    for (int i = 0; i < W; i++)
    {
        arr[i] = (int*)malloc(sizeof(int) * H);
    }
    //创建一个二维数组，并且把里面的值都赋值为1
    //思路：先从第一个开始放蛋糕遍历行如果有不合适的就将数组里面的值改为0，然后继续读最后遍历一遍还为1的count++
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
                //距离2的都不能够放
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