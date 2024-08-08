#pragma once
#include<iostream>
using namespace std;
class noncopyable
{
public:
	//noncopyable(const noncopyable&) = delete;
	noncopyable(const noncopyable&n)
	{
		a_ = n.a_;
		cout << "NO" << endl;
	}
	void operator=(const noncopyable&) = delete;
	void set(int a){
		a_ = a;
	}

protected:
	noncopyable() = default;
	~noncopyable() = default;
private:
	int a_;
};