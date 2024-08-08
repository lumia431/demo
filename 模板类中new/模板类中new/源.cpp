
//#define LOGDEBUG(...) SPDLOG_LOGGER_CALL(m_logger,spdlog::level::level_enum::debug,__VA_ARGS__);
//#define LOGERR(...) SPDLOG_LOGGER_CALL(m_logger,spdlog::level::level_enum::err,__VA_ARGS__);
#define For(n) for(int index = 0;index < n;++index)
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<vector>
//#include<output_Container.h>
//#include<spdlog/spdlog.h>
//#include<spdlog/logger.h>
//#include<spdlog/sinks/daily_file_sink.h>
using namespace std;

template <class T>
class ConstPtr
{

public:

    ConstPtr(const T* ptr = 0);
    ~ConstPtr();
    const T* operator->() const;
    const T* rawPtr() const;
protected:
    void operator=(const ConstPtr<T>& mp);
    const T* rawPtr_;

};

template <class T>
ConstPtr<T>::ConstPtr(const T * ptr)
{
    if (ptr)
    {
        rawPtr_ = new T;
        memcpy((T*)rawPtr_, ptr, sizeof(T));
    }
}
template<class T>
ConstPtr<T>::~ConstPtr()
{
    delete rawPtr_;
}
template<class T>
const T* ConstPtr<T>::operator->() const
{
    return rawPtr_;
}

class A {
public:
    string str;
};

int main() {
    A a;
    a.str = "123";
    ConstPtr<A> p(&a);
	system("pause");
	return 0;
}