#ifndef GLOBALAPITYPE_H
#define GLOBALAPITYPE_H

#include <iostream>
#include <string>
#include <vector>

struct ConnectInfo
{
	std::wstring userName;
	std::wstring passWord;

	std::wstring addr;
	unsigned short port = 7000;
	
	ConnectInfo() = default;
	ConnectInfo(const std::wstring &_addr, unsigned short _port = 7000)
		: addr(_addr)
		, port(_port)
	{}
};

#endif