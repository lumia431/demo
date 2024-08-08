#include <iostream>
#include <string>
#include <type_traits>

// 辅助模板函数，用于获取成员变量的类型
template <typename T>
struct member_traits {};

// 模板特化，用于获取成员变量的类型
template <typename ClassType, typename MemberType>
struct member_traits<MemberType ClassType::*>
{
    using type = MemberType;
};

// get函数模板
template <typename ClassType, typename MemberType>
typename member_traits<MemberType ClassType::*>::type getMember(ClassType& obj, MemberType ClassType::* member)
{
    return obj.*member;
}

// set函数模板
template <typename ClassType, typename MemberType>
void setMember(ClassType& obj, MemberType ClassType::* member, const MemberType& value)
{
    obj.*member = value;
}

// 示例类
struct MyClass
{
    int value;
    std::string name;
};

int main()
{
    MyClass obj;
    obj.value = 42;
    obj.name = "John Doe";

    // 使用get函数获取成员变量的值
    int value = getMember(obj, &MyClass::value);
    std::string name = getMember(obj, &MyClass::name);

    // 输出结果
    std::cout << "Value: " << value << std::endl;
    std::cout << "Name: " << name << std::endl;

    // 使用set函数设置成员变量的值
    setMember(obj, &MyClass::value, 100);
    auto n = &MyClass::name;
    setMember(obj, &MyClass::name, std::string("Jane Smith"));

    // 输出修改后的结果
    std::cout << "Modified Value: " << obj.value << std::endl;
    std::cout << "Modified Name: " << obj.name << std::endl;

    return 0;
}
