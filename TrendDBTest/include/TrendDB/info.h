#pragma once

namespace RTDB
{
    namespace ApiCpp
    {
        class Info;
    }
}

class DBAPI_DLLENTRY RTDB::ApiCpp::Info
{
public:
    Info(void);
    ~Info(void);

    static int32_t GetGroupInfo(int32_t connecter, std::vector <GroupInfo> &groupInfoList);
    static int32_t GetGroupCount(int32_t connecter);

    static int32_t GetTagInfoByTagID(int32_t connecter, const std::vector <int32_t> &tagIDList, std::vector <TagInfo> &tagInfoList);
    static int32_t GetTagInfoByTagName(int32_t connecter, const std::vector <std::wstring> &tagNameList, std::vector <TagInfo> &tagInfoList);

    static int32_t GetTagCount(int32_t connecter);

    static int32_t GetTagIDByGroup(int32_t connecter, const std::wstring &group, std::vector <int32_t> &tagIDList);
    static int32_t GetTagIDByTagName(int32_t connecter, const std::vector <std::wstring> &tagNameList, std::vector <int32_t> &tagIDList);

    static int32_t FuzzyGetTagIDByTagName(
		int32_t connecter, 
        const std::wstring &tagPartName,
		std::vector<int32_t> &tagIDList, 
        std::vector <std::wstring> &tagNameList,
		std::vector <std::wstring> &tagDescriptionList);
    static int32_t FuzzyGetTagIDByTagDescription(
		int32_t connecter, 
        const std::wstring &tagPartDescription,
		std::vector<int32_t> &tagIDList, 
        std::vector <std::wstring> &tagNameList,
		std::vector <std::wstring> &tagDescriptionList);

	static int32_t FuzzyGetTagIDByTagNameEx(
		int32_t connecter,
		const std::wstring &tagPartName,
		const std::wstring &tagGroup,
		std::vector<int32_t> &tagIDList);

	static int32_t FuzzyGetTagIDByTagDescriptionEx(
		int32_t connecter,
		const std::wstring &tagPartDescription,
		const std::wstring &tagGroup,
		std::vector<int32_t> &tagIDList);

	static int32_t FuzzyGetTagIDByStr(
		int32_t connecter,
		const std::wstring &str,
		const std::wstring &tagGroup,
		std::vector<int32_t> &tagIDList);

    static int32_t GetTagBasicInfoByTagID(
		int32_t connecter, 
        const std::vector <int32_t> &tagIDList, 
		std::vector <TagBasicInfo> &tagBasicInfoList);
    static int32_t GetTagBasicInfoByTagName(
		int32_t connecter, 
        const std::vector <std::wstring> &tagNameList, 
		std::vector <TagBasicInfo> &tagBasicInfoList);

	static int32_t GetTagIDInRecycleBin(
		int32_t connecter, 
		std::vector<int32_t> &tagIDs);

	static int32_t GetDeleteTagByTagID(
		int32_t connecter,
		const std::vector<int32_t> &tagIDs,
		std::vector<TagBasicInfo> &tagInfos);

    static int32_t GetTagBasicInfoInRecycleBin(
		int32_t connecter, 
		std::vector <TagBasicInfo> &tagBasicInfoList);
    static int32_t GetTagBasicInfo(
		int32_t connecter, 
		std::vector <TagBasicInfo> &tagBasicInfoList);

    static int32_t GetCalculateTagByGroup(
		int32_t connecter, 
        const std::wstring &group,
		std::vector <CalculateTagInfo> &calculateTagInfoList);
    static int32_t GetCalculateTagSyncID(int32_t connecter);
    static int32_t ResetCalculateTagSyncID(int32_t connecter);
};
