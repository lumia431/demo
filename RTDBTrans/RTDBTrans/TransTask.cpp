#include "pch.h"
#include "TransTask.h"
#include "uaTrans.h"
#include "tsdbTrans.h"
#include "mqttTrans.h"
#include "kafkaTrans.h"
using namespace trans;
using namespace RTDB::ApiCpp;
TransTask::TransTask(TransInfo &info) :m_info(info), m_logger(info.logger)
{
}

TransTask::~TransTask()
{
	Manage::Disconnect(m_apiHandle);
}

int TransTask::Init()
{
	ReadPoint();
	if (m_info.interval < 1000)
	{
		return INTERVALERROR;
	}
	if (m_tagNames.size() == 0)
	{
		LOGINFO("point empty !");
		return POINTEMPTY;
	}
	m_addr = StringToWstring(m_info.rtdbAddr);
	m_port = m_info.rtdbPort;
	m_apiHandle = Manage::Connect(m_addr, m_port);
	if (m_apiHandle < 0)
	{
		LOGINFO("rtdb connect fail! addr = {},port = {}", m_info.rtdbAddr,m_port);
		return RTDBCONNECTERROR;
	}
	std::vector <TagBasicInfo>tagInfoList;
	int ret = Info::GetTagBasicInfoByTagName(m_apiHandle, m_wtagNames, tagInfoList);
	if (ret < 0)
	{
		LOGINFO("Get tag info fail , ret ={}", ret);
		return GETINFOERROR;
	}
	for (auto enableMap : m_info.sdkEnable)
	{
		if (enableMap.second)
		{
			if ("ua" == enableMap.first)
			{
				auto uaTrans = std::make_shared<UaTrans>(m_info,m_tagNames);
				m_transList.emplace_back(uaTrans);
				continue;
			}
			if ("tsdb" == enableMap.first)
			{
				auto tsdbTrans = std::make_shared<TsdbTrans>(m_info, tagInfoList);
				m_transList.emplace_back(tsdbTrans);
				continue;;
			}
			if ("mqtt" == enableMap.first)
			{
				m_info.nowTime = time(NULL);
				auto mqttTrans = std::make_shared<MqttTrans>(m_info);
				m_transList.emplace_back(mqttTrans);
				continue;
			}
			if ("kafka" == enableMap.first)
			{
				auto kafkaTrans = std::make_shared<KafkaTrans>(m_info);
				m_transList.emplace_back(kafkaTrans);
				continue;
			}
		}
	}
	if (m_transList.empty())
	{
		LOGINFO("transSdk empty!");
		return TRANSEMPTY;
	}
	return 0;
}

int TransTask::Run()
{

	m_thrGetValue = std::thread(&TransTask::GetValueThread, this);
	m_thrGetValue.detach();

	for (auto &tran : m_transList)
	{
		std::thread thr([&]() {

			int ret = tran->Connect();

			if (ret < 0)
			{
				LOGINFO("SDK Connect fail , ret = {}", ret);
				return;
			}

			while (!cancelFlg)
			{
				if (!m_tagDataList.empty())
				{
					m_valueMutex.lock_shared();

					ret = tran->Send(m_tagNames, m_tagDataList);

					m_valueMutex.unlock_shared();

					if (ret < 0)
					{
						LOGINFO("SDK Send fail , ret = {}", ret);
						tran->Reconnect();
						Sleep(m_info.interval);
						continue;
					}
				}
				Sleep(m_info.interval);
			}
		});
		thr.detach();
	}
	return 0;
}

std::wstring inline TransTask::StringToWstring(const std::string str)
{
	unsigned len = str.size() * 2;// 预留字节数
	setlocale(LC_CTYPE, "");     //必须调用此函数
	wchar_t *p = new wchar_t[len];// 申请一段内存存放转换后的字符串
	mbstowcs(p, str.c_str(), len);// 转换
	std::wstring str1(p);
	delete[] p;// 释放申请的内存
	return str1;
}

int trans::TransTask::ReadPoint()
{
	std::ifstream istrm(m_info.pointPath);
	std::string tagName;
	while (std::getline(istrm, tagName))
	{
		if (tagName.size() > 0)
		{
			m_tagNames.push_back(tagName);
			m_wtagNames.push_back(StringToWstring(tagName));
		}
	}

	LOGDEBUG("read tag size = {}", m_tagNames.size());
	return 0;
}

int trans::TransTask::GetValueThread()
{
	while (true)
	{
		if (!Manage::Connected(m_apiHandle))
		{
			Manage::Disconnect(m_apiHandle);
			m_apiHandle = Manage::Connect(m_addr, m_port);
			if (m_apiHandle < 0)
			{
				Manage::Disconnect(m_apiHandle);
				LOGINFO("rtdb reconnect fail!");
				Sleep(1000);
				continue;
			}
		}
		m_valueMutex.lock();
		int ret = Realtime::GetValueByTagName(m_apiHandle, m_wtagNames, m_tagDataList);
		m_valueMutex.unlock();
		if (ret <= 0)
		{
			LOGINFO("get value fail ,ret = {}", ret);
			continue;
		}
		if (ret != m_tagNames.size())
		{
			LOGINFO("get value fail ,ret = {}", ret);
		}
		Sleep(m_info.interval);
	}
	return 0;
}
