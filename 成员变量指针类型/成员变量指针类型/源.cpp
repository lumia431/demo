#define For(n) for(int index = 0;index < n;++index)
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<vector>
#include<string.h>
using namespace std;
struct MyClass {
    int value;
};
std::vector<int> GetSplitLen(const std::string& str, const std::string& pattern)
{
    std::vector<int> resVec;
    if ("" == str)
    {
        return resVec;
    }
    //方便截取最后一段数据
    std::string strs = str + pattern;

    size_t pos = strs.find(pattern);
    size_t size = strs.size();
    while (pos != std::string::npos)
    {
        std::string x = strs.substr(0, pos);
        resVec.push_back(x.size());
        strs = strs.substr(pos + pattern.size(), size);
        pos = strs.find(pattern);
    }

    return resVec;
}
void SplitStr(const std::string& str, std::vector<std::string>& tokens, const std::string delim = "_")
{
    tokens.clear();

    auto start = str.find_first_not_of(delim, 0);       // 分割到的字符串的第一个字符
    auto position = str.find_first_of(delim, start);    // 分隔符的位置
    while (position != std::string::npos || start != std::string::npos) {
        // [start, position) 为分割下来的字符串
        tokens.emplace_back(std::move(str.substr(start, position - start)));
        start = str.find_first_not_of(delim, position);
        position = str.find_first_of(delim, start);
    }
}

void Tokenize(const string& str, vector<string>& tokens, const string& delimiters)
{
    // Skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    string::size_type pos = str.find_first_of(delimiters, lastPos);
    while (string::npos != pos || string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}

std::vector<std::string> splitWithStl(const std::string& str, const std::string& pattern)
{
    std::vector<std::string> resVec;
    if ("" == str)
    {
        return resVec;
    }
    //方便截取最后一段数据
    std::string strs = str + pattern;

    size_t pos = strs.find(pattern);
    size_t size = strs.size();
    while (pos != std::string::npos)
    {
        std::string x = strs.substr(0, pos);
        resVec.push_back(x);
        strs = strs.substr(pos + pattern.size(), size);
        pos = strs.find(pattern);
    }

    return resVec;
}

int main() {
    MyClass obj;
    int MyClass::* ptr = &MyClass::value;
    //auto p = *ptr;
    // 访问和修改成员变量的值
    obj.*ptr = 42;
    int value = obj.*ptr;
    string str{ "asddasdjabldlsjdablkjkaabb" };
    vector<int> v;
    auto vv = GetSplitLen(str, "ab");
    auto s1 = "abcdef";
    auto s2 = "cd";
    std::string temp(s1 + 2, 2);
    auto b = strcmp(temp.c_str(), s2);
    return 0;
}
