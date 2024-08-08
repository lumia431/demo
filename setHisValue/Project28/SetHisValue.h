#pragma once
#include <vector>
#include <sstream>
#include "RTDBApi.h"
#include "commtypes.h"
//#include "GlobalDBApi.h"
#include <direct.h>
#include <fstream>
#include <windows.h>
#include <map>
#include <set>
#include "spdlog/spdlog.h"
using namespace  std;
class SetHisValue
{
public:
	SetHisValue() = default;
	~SetHisValue();
	void Run();
	int Init();
	
private:
	void Test();
	void getFiles();
	int getTagName();
	int WriteTagName(string &strArg);
	int GetData();
	int GetDatas();
	int SetValue();
	void WriteLog(std::string log);
	void DataProcess(string &data_, vector<string>&dat);
	void SplitTagName(const string& s, vector<string>& v, const string& c);
	map<string, vector<string>>m_Test;
	string filePath;
	string m_prefix;
	vector<string>m_fileName;
	set<string>m_tagNames;
	map<string,vector<TagData>>m_Datas;
	RTDB::ApiCpp::GlobalDBApi m_dbApi;
	ConnectInfo m_info;
	bool connectflg = true;
	bool testflg = false;
	int interval = 1000;
	string dbID_ ;
};
time_t StrToTime(const std::string& str);
std::wstring StringToWstring(const std::string str);
void Time_tToFileTime(time_t t, FILETIME *ft);
void SplitString(const string& s, vector<string>& v, const string& c);

