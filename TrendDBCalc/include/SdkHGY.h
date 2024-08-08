#pragma once

#include "SdkUnpack.h"

class SdkHGY :virtual public SdkUnpack
{

	typedef time_t(SdkHGY:: *func)(std::string);

public:

	static std::shared_ptr<SdkUnpack>CreateSdkHGY()
	{
		return std::make_shared<SdkHGY>();
	}

	SdkHGY() = default;

	virtual int Init(SetValueInfo info_) override;

	virtual int GetData(std::map<std::string, std::vector<TagData>>&Datas) override;

	virtual int GetTagNames(std::set<std::string>&tagNames) override;

	auto GetMylog()
	{
		return m_logger;
	}

private:

	SetValueInfo m_info;

	void SplitTagName(const std::string & s, std::vector<std::string>& v, const std::string & c);

	std::vector<std::string>m_fileLists;

	std::vector<func>funcList;

	std::shared_ptr<spdlog::logger> m_logger;
	time_t TimeConvert1(std::string timeStr);
	time_t TimeConvert2(std::string timeStr);
	time_t TimeConvert3(std::string timeStr);
	time_t TimeConvert4(std::string timeStr);
};

BOOST_DLL_ALIAS(
	SdkHGY::CreateSdkHGY,
	CreateSdk
)
