#include<iostream>
#include"core/my_add.hpp"
#include"core/my_sub.hpp"
#include"core/my_mul.hpp"
#include"core/my_div.hpp"
using namespace std;
using namespace cov;
int main(){
    auto a = add(1,2);
    auto b = sub(1,2);
    auto d = cov::div(1,2);
}