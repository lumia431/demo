#define For(n) for(int index = 0;index < n;++index)
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<vector>
#include<stdlib.h>
using namespace std;

void test1()
{
    int* p = (int*)malloc(20 * sizeof(int));
    int* pp = (int*)calloc(20, sizeof(int));
    int i;

    printf("malloc申请的空间值:\n\n");
    for (i = 0; i < 20; i++)
    {
        printf("%d ", *p++);
    }
    printf("\n\n");
    printf("calloc申请的空间的值:\n\n");
    for (i = 0; i < 20; i++)
    {
        printf("%d ", *pp++);
    }
    printf("\n");
}

void test2()
{
    char* str = NULL;

    // 分配一个长度为 10 的字符串
    str = (char*)malloc(10 * sizeof(char));
    if (str == NULL) {
        printf("Error: memory allocation failed.\n");
        exit(1);
    }

    // 将字符串初始化为 "Hello"
    strcpy(str, "Hello");
    strcpy(str + 5, ", 123world!");
    // 扩展字符串长度为 20
    str = (char*)realloc(str, 20 * sizeof(char));
    if (str == NULL) {
        printf("Error: memory allocation failed.\n");
        exit(1);
    }

    // 将新的 10 个字符初始化为 ", world!"
    strcpy(str + 5, ", world!");

    // 输出新字符串
    printf("New string: %s\n", str);

    // 释放内存
    free(str);
}

int main() {
    test1();
    test2();
	system("pause");
	return 0;
}