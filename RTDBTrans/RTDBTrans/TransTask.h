#pragma once
#include "TransSdk.h"
#include "TransConfig.h"
#include <fstream>
#include <shared_mutex>
namespace trans
{
	class TransTask
	{
	public:
		TransTask(TransInfo &info);
		~TransTask();
		int Init();
		int Run();
		std::wstring StringToWstring(const std::string str);
		std::atomic_bool cancelFlg = false;
	private:
		TransInfo m_info;
		int m_apiHandle;
		std::wstring m_addr;
		int m_port;
		int ReadPoint();
		int GetValueThread();
		std::vector<TagData>m_tagDataList;
		std::vector<std::wstring> m_wtagNames;
		std::vector<std::string> m_tagNames;
		std::shared_mutex m_valueMutex;
		std::vector<std::shared_ptr<TransSdk>> m_transList;
		std::thread m_thrGetValue;
		std::shared_ptr<spdlog::logger>m_logger;
	};
}

