#define LOGDEBUG(...) SPDLOG_LOGGER_CALL(m_logger,spdlog::level::level_enum::debug,__VA_ARGS__);
#define LOGINFO(...) SPDLOG_LOGGER_CALL(m_logger,spdlog::level::level_enum::info,__VA_ARGS__);
#define LOGWARN(...) SPDLOG_LOGGER_CALL(m_logger,spdlog::level::level_enum::warn,__VA_ARGS__);
#define LOGERR(...) SPDLOG_LOGGER_CALL(m_logger,spdlog::level::level_enum::err,__VA_ARGS__);
#define _CRT_SECURE_NO_WARNINGS
#define For(n) for(int index = 0;index < n;++index)
#include "simple_web_server/client_http.hpp"
#include "nlohmann/json.hpp"
#include <fstream>
#include <thread>
#include "spdlog/spdlog.h"
#include "spdlog/logger.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/async.h"
#include "pugixml.hpp"
struct StockInfo
{
	std::string code;
	std::string name;
	float rate;
};
std::shared_ptr<spdlog::logger>m_logger;
std::vector<std::string> m_tagNameList;
std::vector<StockInfo> g_vecStockList;
void SplitStr(const std::string& str, std::vector<std::string>& tokens, const std::string delim = "_")
{
	tokens.clear();

	auto start = str.find_first_not_of(delim, 0);       // 分割到的字符串的第一个字符
	auto position = str.find_first_of(delim, start);    // 分隔符的位置
	while (position != std::string::npos || start != std::string::npos) {
		// [start, position) 为分割下来的字符串
		tokens.emplace_back(std::move(str.substr(start, position - start)));
		start = str.find_first_not_of(delim, position);
		position = str.find_first_of(delim, start);
	}
}
int ReadCfg()
{
	std::ifstream ifs("D:\\config2.ini");
	std::string str;
	if (!ifs)
	{
		return -1;
	}
	StockInfo stock;
	while (getline(ifs, str))
	{
		std::vector<std::string>v;
		SplitStr(str, v, ",");
		stock.code = v[0];
		stock.name = v[1];
		g_vecStockList.emplace_back(stock);
	}
}
int main()
{
	auto httpClientPtr = std::make_shared<SimpleWeb::Client<SimpleWeb::HTTP>>("qt.gtimg.cn");
	ReadCfg();
	while (1)
	{
		std::ofstream ofs("D:\\DA202106210001_6_55000_25000.txt", std::ios::trunc);
		char ch[10] = {};
		time_t tNow = time(NULL);
		strftime(ch, 10, "%a", localtime(&tNow));
		std::string str(ch);
		if (str == "Sat" || str == "Sun")
		{
			ofs << "week = " << str << std::endl;
			ofs.close();
			Sleep(1000);
			continue;
		}
		else
		{
			char ch[10] = {};
			time_t tNow = time(NULL);
			strftime(ch, 10, "%H", localtime(&tNow));
			std::string str(ch);
			int hour = atoi(str.c_str());
			if (hour < 9 || hour > 15 || hour == 12)
			{
				ofs << "hour = " << hour << std::endl;
				ofs.close();
				Sleep(1000);
				continue;
			}
			//if (hour == 9)
			//{
			//	char ch[10] = {};
			//	time_t tNow = time(NULL);
			//	strftime(ch, 10, "%M", localtime(&tNow));
			//	string str(ch);
			//	int minite = atoi(str.c_str());
			//	if (minite < 30)
			//	{
			//		ofs << "minute = " << minite << endl;
			//		ofs.close();
			//		Sleep(1000);
			//		continue;
			//	}
			//}
			//if (hour == 11)
			//{
			//	char ch[10] = {};
			//	time_t tNow = time(NULL);
			//	strftime(ch, 10, "%M", localtime(&tNow));
			//	string str(ch);
			//	int minite = atoi(str.c_str());
			//	if (minite > 30)
			//	{
			//		ofs << "minute = " << minite << endl;
			//		ofs.close();
			//		Sleep(1000);
			//		continue;
			//	}
			//}
			std::string strUrl = "/q=";
			long size = g_vecStockList.size();
			long iCounter = 0;
			for (long i = 0; i < size; i++)
			{
				std::vector<std::string> splitList;
				auto ret = httpClientPtr->request("GET", "/q=" + g_vecStockList[i].code);
				auto valueStr = ret->content.string();
				SplitStr(valueStr, splitList, "~");
				double diff = std::atof(splitList[3].c_str()) - std::atof(splitList[4].c_str());
				double rate = diff / std::atof(splitList[4].c_str()) * 100.0 + 20;
				g_vecStockList[i].rate = rate;
			}
			std::sort(g_vecStockList.begin(), g_vecStockList.end(), [](const StockInfo&s1, const StockInfo&s2) {
				return s1.rate >= s2.rate; });
				//GetRealtimeInfo(strUrl, g_ssInfo);
				//int stokeSize = g_abbrList.size();
				//for (int i = 0; i < stokeSize; i++)
				//{
				//	double diff = g_ssInfo[i].fCurrent - g_ssInfo[i].fClose;
				//	double rate = diff / g_ssInfo[i].fClose * 100.0 + 10;
				//	if (rate < 0)
				//	{
				//		rate = 0;
				//	}
				//	g_ssInfo[i].rate = rate;
				//	ofs << rate << endl;
				//}
				//std::sort(g_ssInfo.begin(), g_ssInfo.end(), [](const StockStruct&s1, const StockStruct&s2) {
				//	return s1.rate >= s2.rate;
				//});

				pugi::xml_document doc;
				auto child = doc.append_child("Sushine_ZD_Tcp");
				child.append_attribute("tcp_port").set_value(8888);
				child.append_attribute("timeout").set_value(120);
				auto fileLogChild = child.append_child("FileLog");
				fileLogChild.append_attribute("log_level").set_value("Warning");
				auto transChild = child.append_child("KafkaConfig");
				transChild.append_attribute("enable").set_value(false);
				transChild.append_attribute("url").set_value("127.0.0.1:9092");
				transChild.append_attribute("topic").set_value("topic");
				auto trendDBChild = child.append_child("TrendDBConfig");
				trendDBChild.append_attribute("enable").set_value(false);
				trendDBChild.append_attribute("addr").set_value("127.0.0.1");
				trendDBChild.append_attribute("port").set_value(20010);
				auto mqttChild = child.append_child("MqttConfig");
				mqttChild.append_attribute("addr").set_value("127.0.0.1:1883");
				mqttChild.append_attribute("topic").set_value("sys/");
				mqttChild.append_attribute("enable").set_value(false);
				auto warnChild = child.append_child("SushineWarnUrl");
				warnChild.append_attribute("enable").set_value(false);
				warnChild.append_attribute("url").set_value("127.0.0.1:1234");
				auto pgChild = child.append_child("PgsqlConfig");
				pgChild.append_attribute("enable").set_value(false);
				pgChild.append_attribute("addr").set_value("127.0.0.1");
				pgChild.append_attribute("port").set_value("5432");
				pgChild.append_attribute("username").set_value("postgres");
				pgChild.append_attribute("password").set_value("postgres");
				pgChild.append_attribute("db_name").set_value("sushine_db");
				pgChild.append_attribute("charset").set_value("utf-8");
				auto jsonChild = child.append_child("JsonConfigPaths");
				srand(time(NULL));
				For(size)
				{
					std::string str = "DA202107100";
					float rate = g_vecStockList[index].rate;
					if (rate < 20)
					{
						str += "0";
					}
					char buf[10] = {};
					sprintf(buf, "%.1f", rate);
					str += buf;
					str.erase(str.end() - 2);
					std::string jsonPath = "./config/" + str;
					auto jsonTemp = jsonChild.append_child("JsonConfigPath");
					jsonTemp.append_attribute("json_path").set_value(jsonPath.c_str());
					jsonTemp.append_attribute("model_id").set_value(str.c_str());
					jsonTemp.append_attribute("model_desc").set_value(g_vecStockList[index].name.c_str());
					jsonTemp.append_attribute("sampleRate").set_value(5120);
					jsonTemp.append_attribute("dataSize").set_value(8192);
					jsonTemp.append_attribute("log_flag").set_value(true);
				}
				auto saveResult = doc.save_file("D:\\DA202105200002.json");
				//让该线程睡眠xx秒
				::Sleep(1000);
			}
		}
		system("pause");
		return 0;
	}