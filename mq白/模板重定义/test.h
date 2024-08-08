//test.h
#ifndef TEST_TEMPLATE_TEST_H
#define TEST_TEMPLATE_TEST_H
#include<iostream>

//如果print不是一个模板函数，那么编译不通过，报错重复定义
//但如果print是一个函数模板，
template<typename T = void>
void print() {
	std::cout << 6 << std::endl;
}

#endif //TEST_TEMPLATE_TEST_H