#pragma once
#pragma warning(disable:4251)
#ifdef SDKHGY_EXPORTS
#define SDKHGY_API __declspec(dllexport)
#else 
#define  SDKHGY_API __declspec(dllimport)
#endif // LED_EXPORTS

#include "HisDateUnpack.h"

class SDKHGY_API SdkHGY:virtual public HisDateUnpack
{
	typedef time_t(SdkHGY:: *func)(std::string);
public:

	SdkHGY(SetValueInfo info_);

	virtual int Init() override;

	virtual int GetData(std::map<std::string, std::vector<TagData>>&Datas) override;

	virtual int GetTagNames(std::set<std::string>&tagNames) override;

	auto GetMylog()
	{
		return my_logger_;
	}

private:

	SetValueInfo m_info;

	std::vector<func>funcList;

	void SplitTagName(const std::string & s, std::vector<std::string>& v, const std::string & c);

	std::vector<std::string>m_fileLists;

	std::shared_ptr<spdlog::logger> my_logger_;

	time_t TimeConvert1(std::string timeStr);
	time_t TimeConvert2(std::string timeStr);
	time_t TimeConvert3(std::string timeStr);
	time_t TimeConvert4(std::string timeStr);

};

