#pragma once
#pragma warning(disable :4099)
#include "sol/sol.hpp"
#include <map>
#include <QObject>
#include "Log.h"
#include "RTDBApi.h"
#include <atomic>
#include <shared_mutex>
#include <set>
class LuaCal : public QObject
{
	Q_OBJECT

public:
	LuaCal(QObject *parent);
	LuaCal() = default;
	~LuaCal();
	int Init(MyInfo &info, std::shared_ptr<std::map<QString, std::tuple< QString, QString, QString>>>tableData);
	int Run();
	int ConnectTest(MyInfo &info);
	float CalcTest(std::string script);
	int PackTask(std::shared_ptr<std::map<QString, std::tuple< QString, QString, QString>>>tableData);
	std::atomic_bool m_cancleFlg = false;

private:
	void RegistCacheFunctions(sol::state &lua);
	void GetValueThread();
	int UnpackScript(std::string script, std::string patt ,std::vector<std::string> queryList);
	void GetValue(std::vector<TagData> &realDataList, std::vector<int> &hisDataList);
	std::wstring StringToWstring(const std::string str);
	inline void Time_tToFileTime(time_t t, FILETIME *ft);
	std::map<int, std::vector<std::pair<std::wstring, std::string>>> m_data;
	std::map<std::string,float> m_RealDataList;
	std::map<std::string,int> m_HisDataList;
	std::set<std::string> m_RealQuerySet;
	std::set<std::string> m_HisQuerySet;
	std::vector<std::wstring> m_RealWstrQueryList;
	std::vector<std::wstring> m_HisWstrQueryList;
	std::vector<std::string> m_RealStrQueryList;
	std::vector<std::string> m_HisStrQueryList;
	std::vector<TAGID> m_HisIDQueryList;
	std::vector<sol::state> m_luas;
	MyInfo m_info;
	RTDB::ApiCpp::GlobalDBApi m_dbApi;
	ConnectInfo m_dbInfo;
	std::shared_ptr<spdlog::logger>m_logger;
	std::thread m_thr;
	std::shared_mutex m_mutex;
	bool m_iniFlg = false;
};
