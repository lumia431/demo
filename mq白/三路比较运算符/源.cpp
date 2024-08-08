//https://zh.cppreference.com/w/cpp/language/default_comparisons
#include <compare>
struct Point {
    int x;
    int y;
    auto operator<=>(const Point&p) const {
        return x <=> p.x;
    }
    bool operator==(const Point&p) const {
        return x == p.x;
    }
    // ... 非比较函数 ...
};
// 编译器生成全部六个比较运算符
// < <= > >=都可以用 <=>表示

#include <iostream>
#include <set>
int main() {
    Point pt1{ 1, 1 }, pt2{ 1, 2 };
    std::set<Point> s; // ok
    s.insert(pt1);     // ok
    std::cout << std::boolalpha
        << (pt1 == pt2) << ' ' // false；operator== 隐式地采用默认版本
        << (pt1 != pt2) << ' ' // true
        << (pt1 < pt2) << ' ' // true
        << (pt1 <= pt2) << ' ' // true
        << (pt1 > pt2) << ' ' // false
        << (pt1 >= pt2) << ' ';// false
}