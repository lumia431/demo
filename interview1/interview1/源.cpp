
//#define LOGDEBUG(...) SPDLOG_LOGGER_CALL(m_logger,spdlog::level::level_enum::debug,__VA_ARGS__);
//#define LOGERR(...) SPDLOG_LOGGER_CALL(m_logger,spdlog::level::level_enum::err,__VA_ARGS__);
#define For(n) for(int index = 0;index < n;++index)
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<thread>
#include<vector>
#include<unordered_map>
#include<Windows.h>
//#include<output_Container.h>
//#include<spdlog/spdlog.h>
//#include<spdlog/logger.h>
//#include<spdlog/sinks/daily_file_sink.h>
using namespace std;
//std::shared_ptr<spdlog::logger> m_logger;
const int cycle = 1000;
class Page {
public:
	void addCount();
	uint8_t getCount();
	int getId();
private:
	uint8_t m_count;
	int m_id;
};

class LRU {
public:
	void addPage(Page page);
	Page getPage();
private:
	unordered_map<int,Page>m_pages;
};

int main() {

	system("pause");
	return 0;
}

void LRU::addPage(Page page)
{
	m_pages.insert({ page.getId(),page });
}

Page LRU::getPage()
{
	for (auto& page : m_pages) {

	}
	return Page();
}
