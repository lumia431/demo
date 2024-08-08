#include <iostream>
#include <string>
#include <fstream>
using namespace std;
struct MyClass {
    int value;
    double weight;
    string str;
};

int main() {
    MyClass obj;
    obj.value = 42;
    obj.weight = 3.14;
    obj.str = "haha";
    // 序列化对象到文件
    std::ofstream file("data.bin", std::ios::binary);
    file.write(reinterpret_cast<char*>(&obj), sizeof(MyClass));
    file.close();

    // 反序列化对象
    MyClass loadedObj;
    std::ifstream inputFile("data.bin", std::ios::binary);
    inputFile.read(reinterpret_cast<char*>(&loadedObj), sizeof(MyClass));
    inputFile.close();

    std::cout << "Loaded Object: " << loadedObj.value << ", " << loadedObj.weight << std::endl;

    return 0;
}
