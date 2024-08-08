#include<boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include "SetHisValue.h"


SetHisValue::SetHisValue(SetValueInfo info_)
{
	m_info = info_;
	m_logger = info_.my_logger_;
	boost::filesystem::path dllPth = boost::dll::this_line_location().parent_path().parent_path();
	dllPth /= info_.sdk;
	dllPtr_.load(dllPth, boost::dll::load_mode::append_decorations);
	m_unpack = dllPtr_.get_alias<std::shared_ptr<SdkUnpack>()>("CreateSdk")();
	m_dbName = StringToWstring(info_.dbName_);
	m_groupName = StringToWstring(info_.groupName_);
}

SetHisValue::~SetHisValue()
{
	m_Datas.clear();
	LOGDEBUG("use count = {}", m_unpack.use_count());
	m_unpack.reset();
	this->m_dbApi.Disconnect();
	this->m_dbApi.UnSetDefaultInstance();
	
}
//
//************************************
// Method:    Run
// FullName:  SetHisValue::Run
// Access:    public 
// Returns:   int
// Qualifier:
//************************************
int SetHisValue::Run()
{
	int ret = 0;
	if (m_info.mode == MODE::MAKE_FILE)
	{
		ret = m_unpack->GetTagNames(m_tagNames);
		if (ret < 0)
		{
			LOGINFO("Get TagName fail,ret = {}",ret)
			return ret;
		}
		LOGDEBUG("get tag number = {}", m_tagNames.size());
		std::vector<TagInfo>tagInfo;
		std::vector<int32_t>resultList;
		GroupInfo g_info(m_groupName);
		std::vector<GroupInfo>groupList({g_info});
		m_dbApi.AddGroup(m_dbName, groupList, resultList);
		for (auto tagName:m_tagNames)
		{
			std::wstring wTagName = StringToWstring(m_info.prefix_ + tagName);
			TagInfo tag(wTagName, L"7", m_groupName, m_dbName, 1, 0.3);
			tag.timePrecision = 0;
			tagInfo.push_back(tag);
		}
		ret = m_dbApi.AddTag(m_dbName, tagInfo, resultList);
		if (ret != tagInfo.size())
		{
			LOGINFO("Add Tag fail ,ret = {}", ret);
		}
		finishFlg = true;
	}
	else
	{
		ret = m_unpack->GetData(m_Datas);
		m_info.totalProgress_ = ret;
		if (ret< 1)
		{
			LOGINFO("Unpack fail , ret = {}", ret);
			return ret;
		}
		thr_ = std::thread(&SetHisValue::SetValue, this);
		thr_.detach();
	}
	return 0;
}
//
//************************************
// Method:    Init
// FullName:  SetHisValue::Init
// Access:    public 
// Returns:   int
// Qualifier:
//************************************
int SetHisValue::Init()
{
	int ret = m_unpack->Init(m_info);

	if (ret < 0)
	{
		LOGINFO("SDK init fail ,ret = {}", ret);
		return ret;
	}

	m_dbInfo.addr = StringToWstring(m_info.addr_);
	m_dbInfo.port = m_info.port_;
	//if (m_dbApi.Connect(m_dbInfo) < 0)
	//{
	//	LOGINFO("connect rtdb error");
	//	return CONNECTERROR;
	//}
	return 0;
}
//
//************************************
// Method:    GetProGress
// FullName:  SetHisValue::GetProGress
// Access:    public 
// Returns:   double
// Qualifier:
//************************************
double SetHisValue::GetProGress()
{
	if(m_info.totalProgress_>1)
	return progress_ / (m_info.totalProgress_ *1.0);
	else return 0.0;
}
//
//************************************
// Method:    SetValue
// FullName:  SetHisValue::SetValue
// Access:    private 
// Returns:   int
// Qualifier:
//************************************
int SetHisValue::SetValue()
{
	std::vector<std::wstring>tagname;
	std::vector <TAGID> tagIDList;
	for (auto &datas : m_Datas)
	{

		tagname.push_back(StringToWstring(m_info.dbName_ + "." + datas.first));
		if (m_dbApi.GetTagIDByTagName(tagname, tagIDList) < 0)
		{
			LOGINFO("get tagID error tagName = {}", datas.first);
			continue;
		}
		tagID_ = tagIDList.front().tagID;
		long scanIdx = 1;
		while (!cancelFlg)
		{
			if (pauseStatus)
			{
				continue;
			}
			if (!m_dbApi.Connected())
			{
				LOGINFO( "RTDB disconnect" );
				while (1)
				{
					if (m_dbApi.Connect(m_dbInfo) >= 0)
					{
						LOGINFO("RTDB reconnect success");
						break;
					}
					Sleep(10000);
				}
			}
			if ((scanIdx*m_info.interval) > datas.second.size())
			{

				std::vector<TagData>data_(datas.second.begin() + (m_info.interval*(scanIdx - 1)), datas.second.end());
				int ret = m_dbApi.SetHistoryValues(tagIDList.back(), data_);
				if (ret >= 0)
				{
					LOGDEBUG("set value success tagID = {}", std::to_string(tagIDList.back().tagID));


				}
				else
				{
					LOGDEBUG("set value fail tagID = {}", std::to_string(tagIDList.back().tagID));

				}
				break;
			}
			std::vector<TagData> data_(datas.second.begin() + (m_info.interval*(scanIdx - 1)), datas.second.begin() + (m_info.interval)*scanIdx);
			int ret = m_dbApi.SetHistoryValues(tagIDList.back(), data_);
			if (ret >= 0)
			{
				LOGDEBUG("set value success tagID = {}" , std::to_string(tagIDList.back().tagID));

			}
			else
			{
				LOGDEBUG("set value fail tagID = {}" , std::to_string(tagIDList.back().tagID));
			}
			scanIdx++;
		}
		scanIdx = 1;
		progress_++;
		tagIDList.clear();
		tagname.clear();
	}
	LOGINFO("set history over" );
	finishFlg = true;
	return 0;
}
//
//************************************
// Method:    StringToWstring
// FullName:  SetHisValue::StringToWstring
// Access:    private 
// Returns:   std::wstring
// Qualifier:
// Parameter: const std::string str
//************************************
std::wstring SetHisValue::StringToWstring(const std::string str)
{
	unsigned len = str.size() * 2;// 预留字节数
	setlocale(LC_CTYPE, "");     //必须调用此函数
	wchar_t *p = new wchar_t[len];// 申请一段内存存放转换后的字符串
	mbstowcs(p, str.c_str(), len);// 转换
	std::wstring str1(p);
	delete[] p;// 释放申请的内存
	return str1;
}


