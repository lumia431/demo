#pragma once
#include <string>
#include <functional>

#include "SerialPortConfig.h"

class SerialPort
{
public:
	SerialPort(SerialPortConfig conf);
	~SerialPort();

	bool Open(bool enableCallback = false);
	bool Close();

	bool RegisterCallBack(std::function<void(const std::string &, void *)> callBack, void *param);
	bool UnregisterCallBack();

	std::string Read(uint32_t dataLen = 1024);
	bool Write(const std::string &contents);

private:
	struct SerialInfo;
	SerialInfo *data_;
};

