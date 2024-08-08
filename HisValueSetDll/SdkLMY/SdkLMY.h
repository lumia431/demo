#pragma once

#include "SdkUnpack.h"

class SdkLMY :virtual public SdkUnpack
{
public:

	static std::shared_ptr<SdkUnpack>CreateSdkLMY()
	{
		return std::make_shared<SdkLMY>();
	}

	SdkLMY() = default;

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

	std::shared_ptr<spdlog::logger> m_logger;

};

BOOST_DLL_ALIAS(
	SdkLMY::CreateSdkLMY,
	CreateSdk
)
