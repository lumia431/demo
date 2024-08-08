#include <iostream>
#include <string>
#include <fstream>
using namespace std;

/*
异常的逐层传递:如果在catch块内捕捉到一个异常, 但是该块内代码无法或者不想处理它,
可以继续抛出给上层调用者处理, 直至到最外层的封闭try块
*/

void funcOfNo70() throw (string);

void test1OfMEH();

ofstream log_no70("log_no70.txt", ios::app);

int main() {
    try
    {
        funcOfNo70();
    }
    catch (exception e)
    {
        cout << e.what() << endl;
    }
    log_no70.close();
    return 0;
}

void funcOfNo70() throw(string)
{
    throw exception("123");
}

void test1OfMEH()
{
    log_no70 << "throw a string type exception!" << endl;
    throw "error";
}