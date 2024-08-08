#include "LuaCal.h"
#include <regex>
using namespace RTDB::ApiCpp;

LuaCal::LuaCal(QObject *parent)
	: QObject(parent)
{
}

LuaCal::~LuaCal()
{
	if (m_dbApi.Connected())
	{
		this->m_dbApi.Disconnect();
		this->m_dbApi.UnSetDefaultInstance();
	}
}

int LuaCal::Init(MyInfo &info, std::shared_ptr<std::map<QString, std::tuple<QString, QString, QString>>>tableData)
{
	m_info = info;
	m_dbInfo.addr = m_info.addr;
	m_dbInfo.port = m_info.port;
	m_logger = m_info.logger;
	m_data.clear();
	m_RealDataList.clear();
	m_RealQuerySet.clear();
	m_RealWstrQueryList.clear();
	m_RealStrQueryList.clear();
	m_HisQuerySet.clear();
	m_HisStrQueryList.clear();
	m_HisIDQueryList.clear();
	m_HisWstrQueryList.clear();
	m_HisDataList.clear();
	try
	{
		if (m_dbApi.Connected())
		{
			m_dbApi.Disconnect();
		}
		if (m_dbApi.Connect(m_dbInfo) < 0)
		{
			LOGINFO("connect rtdb error");
			return CONNECTERROR;
		}
	}
	catch (const std::exception&)
	{
		LOGINFO("connect rtdb error");
		return CONNECTERROR;
	}
	if (PackTask(tableData) < 0)
	{
		LOGINFO("pack task error!");
		return PACKERROR;
	}
	LOGDEBUG("real value size = {}", m_RealStrQueryList.size());
	LOGDEBUG("his value size = {}", m_HisStrQueryList.size());
	if (m_data.empty())
	{
		LOGINFO("data size = 0");
		return PACKERROR;
	}
	m_iniFlg = true;
	return 0;
}

int LuaCal::Run()
{
	if (!m_iniFlg) return INITERROR;
	m_thr = std::thread(&LuaCal::GetValueThread, this);
	m_thr.detach();
	int index = 0;
	std::vector<std::thread> thrList;
	for (auto &data : m_data)
	{
		sol::state &lua = m_luas[index];
		index++;
		RegistCacheFunctions(lua);
		thrList.push_back(std::thread([&lua, &data, this]() {
			while (!m_cancleFlg)
			{
				std::vector<std::wstring>tagNameList;
				std::vector<TagData> tagDataList;
				std::vector<int32_t> resultList;
				TagData tag;
				time_t t = time(NULL);
				FILETIME ft;
				Time_tToFileTime(t, &ft);
				tag.status = 1;
				tag.timestamp = ft;
				{
					std::lock_guard<std::shared_mutex> lockGuard(m_mutex);
					try
					{
						for (auto &dat : data.second)
						{
							lua.script(dat.second);
							sol::function mainFun = lua["Main"];
							float value = mainFun();
							LOGDEBUG("value = {} tagName = {}", value, QString::fromStdWString(dat.first).toStdString());
							tag.value = value;
							tagDataList.push_back(tag);
							tagNameList.push_back(dat.first);
						}
					}
					catch (const std::exception&e)
					{
						LOGINFO("catch exception {}", e.what());
					}
				}
				int ret = m_dbApi.SetValueByTagNameNoTime(tagNameList, tagDataList, resultList);
				LOGDEBUG("set value over ,tagNameList.size = {}", tagNameList.size());
				if (ret != tagNameList.size())
				{
					LOGINFO("set value fail , ret = {}", ret);
				}
				Sleep(data.first);
			}
			}));
	}
	For(thrList.size())
	{
		thrList[index].join();
	}
	return 0;
}

int LuaCal::ConnectTest(MyInfo &info)
{
	m_info = info;
	m_dbInfo.addr = m_info.addr;
	m_dbInfo.port = m_info.port;
	m_logger = m_info.logger;
	try
	{
		if (m_dbApi.Connected())
		{
			m_dbApi.Disconnect();
		}
		if (m_dbApi.Connect(m_dbInfo) < 0)
		{
			LOGINFO("connect rtdb error");
			return CONNECTERROR;
		}
	}
	catch (const std::exception&)
	{
		LOGINFO("connect rtdb error");
		return CONNECTERROR;
	}
	return 0;
}

float LuaCal::CalcTest(std::string script)
{
	float value = 0.0;
	try
	{
		sol::state lua;
		RegistCacheFunctions(lua);
		std::vector<TagData> realDataList;
		std::vector<int> hisDataList;
		GetValue(realDataList, hisDataList);
		for (int index = 0; index < m_RealStrQueryList.size(); index++)
		{
			m_RealDataList[m_RealStrQueryList[index]] = realDataList[index].value;
		}
		for (int j = 0; j < m_HisStrQueryList.size(); j++)
		{
			m_HisDataList[m_HisStrQueryList[j]] = hisDataList[j];
		}
		LOGDEBUG("get value over m_RealStrQueryList.size() = {} m_HisStrQueryList.size() ={}", m_RealDataList.size(), m_HisDataList.size());
		lua.script(script);
		sol::function mainFun = lua["Main"];
		value = mainFun();
	}
	catch (const std::exception&e)
	{
		LOGINFO("catch exception {}", e.what());
		return -1.0;
	}
	return value;
}

int LuaCal::PackTask(std::shared_ptr<std::map<QString, std::tuple< QString, QString, QString>>>tableData)
{
	std::string realStr("GetValue\\(\"(.*?)\"\\)");
	std::string hisStr("CheckValue\\(\"(.*?)\"\\)");
	for (auto &data : *tableData)
	{
		std::vector<std::string> queryRealList;
		std::vector<std::string> queryHisList;
		UnpackScript(std::get<1>(data.second).toStdString(), realStr, queryRealList);
		UnpackScript(std::get<1>(data.second).toStdString(), hisStr, queryHisList);

		for (auto &data : queryRealList)
		{
			m_RealQuerySet.insert(data);
		}
		for (auto &data : queryHisList)
		{
			m_HisQuerySet.insert(data);
		}
		int interval = std::get<2>(data.second).toInt();
		m_data[interval].push_back(std::make_pair<std::wstring, std::string>(data.first.toStdWString(), std::get<1>(data.second).toStdString()));
	}
	for (auto &queryList : m_RealQuerySet)
	{
		m_RealWstrQueryList.emplace_back(StringToWstring(queryList));
		m_RealStrQueryList.emplace_back(queryList);
	}
	for (auto &queryList : m_HisQuerySet)
	{
		m_HisWstrQueryList.emplace_back(StringToWstring(queryList));
		m_HisStrQueryList.emplace_back(queryList);
	}
	m_luas.resize(m_data.size());
	if (m_HisWstrQueryList.empty()) return 0;
	auto ret = m_dbApi.GetTagIDByTagName(m_HisWstrQueryList, m_HisIDQueryList);
	if (ret < 0 || m_HisIDQueryList.empty())
	{
		LOGINFO("Get tagID fail , ret = {}", ret);
	}
	return 0;
}

void LuaCal::RegistCacheFunctions(sol::state &lua)
{
	lua.open_libraries();
	lua.set_function("GetValue",
		[&](const std::string& name)
		{
			return m_RealDataList[name];
		});
	lua.set_function("CheckValue",
		[&](const std::string& name)
		{
			return m_HisDataList[name];
		});
}

void LuaCal::GetValueThread()
{
	while (!m_cancleFlg)
	{
		if (!m_dbApi.Connected())
		{
			LOGINFO("Rtdb disconnected !");
			if (m_dbApi.Connect(m_dbInfo) < 0)
			{
				LOGINFO("Rtdb reconnect fail !");
				Sleep(1000);
				continue;
			}
		}
		std::vector<TagData> realDataList;
		std::vector<int> hisDataList;
		GetValue(realDataList, hisDataList);
		m_mutex.lock();
		for (int index = 0; index < m_RealStrQueryList.size(); index++)
		{
			m_RealDataList[m_RealStrQueryList[index]] = realDataList[index].value;
		}
		for (int j = 0; j < m_HisStrQueryList.size(); j++)
		{
			m_HisDataList[m_HisStrQueryList[j]] = hisDataList[j];
		}
		LOGDEBUG("get value over m_RealStrQueryList.size() = {} m_HisStrQueryList.size() ={}", m_RealDataList.size(), m_HisDataList.size());
		m_mutex.unlock();
		Sleep(1000);
	}
}

int LuaCal::UnpackScript(std::string script, std::string patt ,std::vector<std::string> queryList)
{
	std::regex pattern(patt);
	std::smatch result;
	//迭代器声明
	std::string::const_iterator iterStart = script.begin();
	std::string::const_iterator iterEnd = script.end();
	std::string temp;
	while (std::regex_search(iterStart, iterEnd, result, pattern))
	{
		temp = std::regex_replace(result[0].str(), pattern, "$1");
		queryList.emplace_back(temp);
		iterStart = result[0].second;	//更新搜索起始位置,搜索剩下的字符串
	}
	return 0;
}

void LuaCal::GetValue(std::vector<TagData> &realDataList, std::vector<int> &hisDataList)
{
	realDataList.resize(m_RealWstrQueryList.size());
	hisDataList.resize(m_HisWstrQueryList.size());
	if (!m_RealWstrQueryList.empty())
	{
		int ret = m_dbApi.GetValueByTagName(m_RealWstrQueryList, realDataList);
		if (ret < 0)
		{
			LOGINFO("Get value fail , ret = {}", ret);
		}
	}
	FILETIME timeEnd;
	FILETIME timeStart;
	time_t tEnd = time(NULL);
	time_t tStart = tEnd - 300;
	Time_tToFileTime(tEnd, &timeEnd);
	Time_tToFileTime(tStart, &timeStart);
	int i = 0;
	LOGDEBUG("get real value over m_HisIDQueryList.size() = {}", m_HisIDQueryList.size());
	for (auto &tagID : m_HisIDQueryList)
	{
		std::vector<TagData> hisTmpList;
		time_t t = time(NULL);
		auto ret = m_dbApi.GetNValues(tagID, timeStart, timeEnd, 10, hisTmpList);
		LOGDEBUG("getnvalue use {}", time(NULL) - t);
		if (ret < 0 || hisTmpList.size() == 0)
		{
			LOGINFO("Get value fail , ret = {} ,tagID = {}", ret, tagID.tagID);
			hisDataList[i] = -1;
			i++;
			continue;
		}
		hisDataList[i] = 0;
		float firstValue = hisTmpList.front().value;
		LOGDEBUG("hisTmpList.size() = {}", hisTmpList.size());
		for (auto &tag : hisTmpList)
		{
			if (tag.value != firstValue)
			{
				hisDataList[i] = 1;
				break;
			}
		}
		i++;
	}
	LOGDEBUG("getvalue mutex over!");
}

inline std::wstring LuaCal::StringToWstring(const std::string str)
{
	unsigned len = str.size() * 2;// 预留字节数
	setlocale(LC_CTYPE, "");     //必须调用此函数
	wchar_t *p = new wchar_t[len];// 申请一段内存存放转换后的字符串
	mbstowcs(p, str.c_str(), len);// 转换
	std::wstring str1(p);
	delete[] p;// 释放申请的内存
	return str1;
}

inline void LuaCal::Time_tToFileTime(time_t t, FILETIME *ft)
{
	LONGLONG ll = Int32x32To64(t, 10000000) + 116444736000000000;
	ft->dwLowDateTime = (DWORD)ll;
	ft->dwHighDateTime = (DWORD)(ll >> 32);
}