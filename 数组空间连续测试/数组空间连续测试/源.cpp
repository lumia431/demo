#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

//在C++中，指针和数组都是用来存储数据的数据类型，但是它们有一些区别：
//
//内存分配方式：数组在定义时就需要分配内存空间，而指针则可以在需要时进行动态内存分配。
//
//内存布局：数组在内存中是一段连续的内存空间，而指针是单个指针变量，它所指向的数据可以分布在内存的任意位置。
//
//操作方式：数组可以直接使用下标来访问元素，而指针需要先解引用再进行访问。例如，对于数组a和指针p，要访问a的第i个元素，可以使用a[i]，而要访问p所指向的第i个元素，则需要使用* (p + i)。
//
//类型检查：数组在定义时需要指定元素的类型和数量，编译器会进行类型检查和元素数量检查。而指针只需要定义指向的数据类型即可，编译器不会进行元素数量的检查，容易发生越界错误。
//
//大小限制：数组的大小在定义时就已经确定，不能改变；而指针没有大小限制，可以通过指针运算来访问多个元素。
//
//需要注意的是，指针和数组之间并不是完全独立的，它们之间存在一些联系。例如，数组名可以看作是一个指向数组首元素的指针，可以通过数组名来访问数组元素；同时，指针也可以被视为一个数组，可以通过指针运算来访问多个元素。此外，指针也可以用来动态地分配和释放数组内存，实现数组的动态增长和缩减。

#ifdef __cplusplus
extern "C" {
#endif
    void C_stack();
    void C_malloc();
    void CXX_stack();
    void CXX_new();
#ifdef __cplusplus
};
#endif

void test(char* buf)
{
    for (int i = 0; i < 2; ++i)
    {
        auto ptr = buf + 4 * i;
        auto tempValue = new char[4 + 1];
        memcpy(tempValue, ptr, 4);
        tempValue[4] = '\0';
        cout << tempValue << '\t';
    }
    cout << endl;
}

void C_stack() {
    printf("====== C stack ======\n");
    char str[2][4] = { {65,66,67,68}, {69,70,71,72} };
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            printf("[%c]%p\t", str[i][j], &str[i][j]);
        }
        printf("\n");
    }
    printf("=====================\n\n");
}
void C_malloc() {
    printf("====== C malloc ======\n");

    char** str = (char**)malloc(2 * sizeof(char*));

    for (int i = 0; i < 2; i++)
        str[i] = (char*)malloc(4 * sizeof(char));
    char s = 'A';
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            str[i][j] = s++;
            printf("[%c]%p\t", str[i][j], &str[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < 2; i++)
        free(str[i]);
    free(str);
    printf("====================\n\n");
}


void CXX_stack() {
    cout << "====== Cpp stack ======" << endl;
    char str[2][4] = { {65,66,67,68}, {69,70,71,72} };
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            cout << "[" << str[i][j] << "]" << (void*)&str[i][j] << "\t";
        }
        cout << endl;
    }
    //这恰恰说明了数组和指针是两种完全不懂的数据结构
    //char[][]表示一个二维字符数组，它在内存中是一块连续的内存空间，每个元素都是一个字符数组，大小都是固定的。
    //char**表示一个指向字符指针的指针，它在内存中是一个指针数组，每个元素都是一个指向字符数组的指针
    //如果把指针看成座位号，char**可以看成座位号的数组，大家可以跳着坐，比如坐1、3、5、8
    test((char*)str);//栈上的二维数组是以连续的内存块的形式存储的，因此数组名等于第一行第一个元素的地址。这是因为数组名本质上是数组首元素的地址
    cout << "======================" << endl << endl;
}
void CXX_new() {
    cout << "====== Cpp new ======" << endl;

    char** str = new char* [2];
    for (int i = 0; i < 2; i++)
        str[i] = new char[4];
    char s = 'A';
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            str[i][j] = s++;
            cout << "[" << str[i][j] << "]" << (void*)&str[i][j] << "\t";
        }
        cout << endl;
    }
    cout << (void*)str << endl;//在C++中，堆上的二维数组是以指针数组的形式存储的，因此数组名并不等于第一行第一个元素的地址，而是指向第一个元素所在的指针的指针
    cout << (void*)*str << endl;//str是一个指向char类型指针的指针，它存储了动态分配的二维数组的地址。由于该数组是以指针数组的形式存储的，因此str指向的是第一行的指针，而不是数组的首地址。
    test((char*)*str);
    for (int i = 0; i < 2; i++)
        delete[]str[i];
    delete str;
    cout << "====================" << endl;
}

void test2()
{
    auto arr = new int[3];
    for (int i = 0; i < 3; ++i)
    {
        arr[i] = i + 8;
    }
    int a = 0;
    memcpy(&a, (char*)arr + 8, 4);

}

int main() {
    test2();
    C_stack();
    C_malloc();
    CXX_stack();
    CXX_new();
    return 0;
}

