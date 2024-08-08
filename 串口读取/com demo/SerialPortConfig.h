#pragma once
#include <cstdint>
#include <string>

// 串口号配置
struct SerialPortConfig
{
	std::string portName ;		// 端口号名称
	uint32_t baudRate;		// 波特率
	uint8_t byteSize ;		// 数据位
	uint8_t parity ;			// 奇偶校验位
	uint8_t stopBits ;		// 停止位
	uint32_t readTimeOut;		// 读超时时间 毫秒 0代表未设置
	uint32_t writeTimeOut;		// 写超时时间 毫秒 0代表未设置

	SerialPortConfig()
	{
		baudRate = 115200;
		byteSize = 8;
		parity = 0;
		stopBits = 0;
		readTimeOut = 2000;
		writeTimeOut = 2000;
	}
};