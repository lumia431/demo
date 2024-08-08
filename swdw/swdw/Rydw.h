#pragma once
//#define LOGDEBUG(...) SPDLOG_LOGGER_CALL(this->m_logger,spdlog::level::level_enum::debug,__VA_ARGS__);
//#define LOGINFO(...) SPDLOG_LOGGER_CALL(this->m_logger,spdlog::level::level_enum::info,__VA_ARGS__);
//#define LOGWARN(...) SPDLOG_LOGGER_CALL(this->m_logger,spdlog::level::level_enum::warn(),__VA_ARGS__);
//#define LOGERR(...) SPDLOG_LOGGER_CALL(this->m_logger,spdlog::level::level_enum::err,__VA_ARGS__);
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define For(n) for(int index = 0;index < n;index++)
#include "crow.h"
#include "mqtt/async_client.h"
//#include "spdlog/spdlog.h"
//#include "spdlog/logger.h"
//#include <spdlog/sinks/daily_file_sink.h>
#include <mutex>
#include <queue>
#include <memory>
#include <WinSock2.h>
#include "TrendDB/RTDBApi.h"
#pragma comment(lib, "ws2_32.lib")
#pragma pack(1)
struct DataType
{
	int head;
	uint16_t len;
	uint16_t type;
	uint16_t floor;
	int ID;
	double x;
	double y;
	double z;
	uint8_t attribute;
	uint16_t status;
	uint8_t reserve[5];
};
struct Place
{
	std::string ID;
	uint16_t floor;
	time_t timeStamp = 0;
	double x;
	double y;
	double z;
};
#pragma pack()
class CollectMonitor
{
public:
	CollectMonitor() = default;
	~CollectMonitor();
	int Init();
	int Run();
private:
	int UdpThr();
	int HttpThr();
	std::wstring StringToWstring(const std::string str);
	void Time_tToFileTime(time_t t, FILETIME *ft);
	int ReadCfg();
	void CalcTagDatasX(time_t startTime, time_t endTime, int period ,std::vector<TagData> &originDatas, std::vector<float> &outDatas);
	void CalcTagDatasY(time_t startTime, time_t endTime, int period, std::vector<TagData> &originDatas, std::vector<float> &outDatas);
	void CalcTagDatasZ(time_t startTime, time_t endTime, int period, std::vector<TagData> &originDatas, std::vector<float> &outDatas);
	//int ReadPoint();
	//std::shared_ptr<spdlog::logger> m_logger;
	std::string m_mqttAddr;
	RTDB::ApiCpp::GlobalDBApi m_dbApi;
	ConnectInfo m_dbInfo;
	std::string m_topic;
	int m_logLevel;
	SOCKET serSock_;
	sockaddr_in dstAddr_;
	std::string listenIp_;
	int listenPort_;
	std::queue<Place> m_dataQueue;
	std::mutex m_mutex;
	int m_interval;
	float m_paraC;
	float m_paraD;
	uint16_t m_httpPort;
	std::string m_url;
};

