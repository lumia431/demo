#include<iostream>
#include<exception>
using namespace std;
class myException :public exception
{
public:
    myException() :exception("ERROR! Don't divide a number by integer zero.\n")
    {
    }
};
//entry of the application  
int main()
{
    int x = 100, y = 0;
    try
    {
        if (y == 0) throw myException();
        else cout << x / y;
    }
    catch (myException& me)
    {
        cout << me.what();
    }
    system("pause");
    return 0;
}