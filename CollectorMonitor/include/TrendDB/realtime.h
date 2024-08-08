#pragma once

namespace RTDB
{
    namespace ApiCpp
    {
        class Realtime;
    }
}

class DBAPI_DLLENTRY RTDB::ApiCpp::Realtime
{
public:
    Realtime(void);
    ~Realtime(void);

    static int32_t GetValueByTagID(
		int32_t connecter, 
		const std::vector <int32_t> &tagIDList,
		std::vector <TagData> &tagDataList);
    static int32_t GetValueByTagName(
		int32_t connecter, 
		const std::vector <std::wstring> &tagNameList,
		std::vector <TagData> &tagDataList);
	static int32_t GetDoubleValueByTagID(
		int32_t connecter,
		const std::vector <int32_t> &tagIDList,
		std::vector <TagDoubleData> &tagDataList);

    static int32_t SetValueByTagID(
        int32_t connecter, 
        const std::vector <int32_t> &tagIDList, 
        const std::vector <TagData> &tagDataList, 
        std::vector <int32_t> &resultList);

	static int32_t SetDoubleValueByTagID(
		int32_t connecter,
		const std::vector <int32_t> &tagIDList,
		const std::vector <TagDoubleData> &tagDataList,
		std::vector <int32_t> &resultList);


    static int32_t SetValueByTagIDNoTime(
        int32_t connecter, 
        const std::vector <int32_t> &tagIDList, 
        const std::vector <TagData> &tagDataList, 
        std::vector <int32_t> &resultList);

	static int32_t SetDoubleValueByTagIDNoTime(
		int32_t connecter,
		const std::vector <int32_t> &tagIDList,
		const std::vector <TagDoubleData> &tagDataList,
		std::vector <int32_t> &resultList);

    static int32_t SetValueByTagName(
        int32_t connecter, 
        const std::vector <std::wstring> &tagNameList, 
        const std::vector <TagData> &tagDataList, 
        std::vector <int32_t> &resultList);

    static int32_t SetValueByTagNameNoTime(
        int32_t connecter, 
        const std::vector <std::wstring> &tagNameList, 
        const std::vector <TagData> &tagDataList, 
        std::vector <int32_t> &resultList);
};
