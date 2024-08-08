#pragma once
#include <memory>
class A
{
public:
	A(int i);
	A() = default;
	~A();
private:
	std::shared_ptr<int>value;
};

