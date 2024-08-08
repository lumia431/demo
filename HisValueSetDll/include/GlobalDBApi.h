// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 GLOBALDBAPI_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// GLOBALDBAPI_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifndef GLOBALDBAPI_H
#define GLOBALDBAPI_H

namespace RTDB
{
	namespace ApiCpp
	{
		class GlobalDBApi;
	}
}


class GlobalDBApi_Impl;
// 此类是从 GlobalDBApi.dll 导出的
class DBAPI_DLLENTRY RTDB::ApiCpp::GlobalDBApi
{
public:
	GlobalDBApi(void);
	~GlobalDBApi();

	// TODO: 在此添加您的方法。

	// Manager
	int Connect(ConnectInfo &connectInfo);
	void Disconnect(void);
	bool Connected();

	int SetDefaultInstance(std::wstring &instanceName);
	void UnSetDefaultInstance(void);

	// RealTime
	int32_t GetValueByTagID(std::vector<TAGID> &tagIDList, std::vector<TagData> &tagDataList);
	int32_t GetDoubleValueByTagID(std::vector<TAGID> &tagIDList, std::vector<TagDoubleData> &tagDataList);
	int32_t GetValueByTagName(std::vector<std::wstring> &tagNameList, std::vector<TagData> &tagDataList);
	int32_t GetDoubleValueByTagName(std::vector<std::wstring> &tagNameList, std::vector<TagDoubleData> &tagDataList);

	int32_t SetValueByTagID(std::vector<TAGID> &tagIDList, std::vector<TagData> &tagDataList, std::vector<int32_t> &resultList);
	int32_t SetValueByTagIDNoTime(std::vector<TAGID> &tagIDList, std::vector<TagData> &tagDataList, std::vector<int32_t> &resultList);
	int32_t SetDoubleValueByTagID(std::vector<TAGID> &tagIDList, std::vector<TagDoubleData> &tagDataList, std::vector<int32_t> &resultList);
	int32_t SetDoubleValueByTagIDNoTime(std::vector<TAGID> &tagIDList, std::vector<TagDoubleData> &tagDataList, std::vector<int32_t> &resultList);
	int32_t SetValueByTagName(std::vector<std::wstring> &tagNameList, std::vector<TagData> &tagDataList, std::vector<int32_t> &resultList);
	int32_t SetValueByTagNameNoTime(std::vector<std::wstring> &tagNameList, std::vector<TagData> &tagDataList, std::vector<int32_t> &resultList);
	int32_t SetDoubleValueByTagName(std::vector<std::wstring> &tagNameList, std::vector<TagDoubleData> &tagDataList, std::vector<int32_t> &resultList);
	int32_t SetDoubleValueByTagNameNoTime(std::vector<std::wstring> &tagNameList, std::vector<TagDoubleData> &tagDataList, std::vector<int32_t> &resultList);

	// ADMIN
	int32_t AddGroup(const std::wstring &dbName, std::vector<GroupInfo> &groupInfoList, std::vector<int32_t> &resultList);
	int32_t DeleteGroup(const std::wstring &dbName, std::vector<GroupInfo> &groupInfoList, std::vector<int32_t> &resultList);

	int32_t AddTag(const std::wstring &dbName, std::vector<TagInfo> &tagInfoList, std::vector<int32_t> &resultList);
	int32_t AlterTag(const std::wstring &dbName, std::vector<TagInfo> &tagInfoList, std::vector<int32_t> &resultList);

	int32_t DeleteTagToRecycleBin(const std::wstring &dbName, std::vector<TAGID> &tagIDList, std::vector<int32_t> &resultList);
	int32_t RestoreTagFromRecycleBin(const std::wstring &dbName, std::vector<TAGID> &tagIDList, std::vector<int32_t> &resultList);
	int32_t DeleteTagFromRecycleBin(const std::wstring &dbName, std::vector<TAGID> &tagIDList, std::vector<int32_t> &resultList);
	int32_t CompletelyDeleteTag(const std::wstring &dbName, std::vector<TAGID> &tagIDList, std::vector<int32_t> &resultList);

	// INFO
	int32_t GetDBList(std::vector<std::wstring> &dbList);
	int32_t GetGroupInfo(const std::wstring &dbName, std::vector <GroupInfo> &groupInfoList);
	int32_t GetGroupCount(const std::wstring &dbName);

	int32_t GetTagInfoByTagID(std::vector <TAGID> &tagIDList, std::vector <TagInfo> &tagInfoList);
	int32_t GetTagInfoByTagName(std::vector <std::wstring> &tagNameList, std::vector <TagInfo> &tagInfoList);

	int32_t GetTagCount(const std::wstring &dbName);
	int32_t GetTagCount();

	int32_t GetTagIDByGroup(const std::wstring &dbName, std::wstring group, std::vector <TAGID> &tagIDList);
	int32_t GetTagIDByTagName(const std::vector <std::wstring> &tagNameList, std::vector <TAGID> &tagIDList);

	int32_t GetTagBasicInfoByTagID(std::vector <TAGID> &tagIDList, std::vector <TagBasicInfo> &tagBasicInfoList);
	int32_t GetTagBasicInfoByTagName(std::vector <std::wstring> &tagNameList, std::vector <TagBasicInfo> &tagBasicInfoList);
	int32_t GetTagBasicInfo(const std::wstring &dbName, std::vector <TagBasicInfo> &tagBasicInfoList);

	int32_t GetCalculateTagByGroup(const std::wstring &dbName, std::wstring group, std::vector <CalculateTagInfo> &calculateTagInfoList);
	int32_t GetCalculateTagSyncID(const std::wstring &dbName);
	int32_t ResetCalculateTagSyncID(const std::wstring &dbName);

	int32_t GetTagBasicInfoInRecycleBin(const std::wstring &dbName, std::vector <TagBasicInfo> &tagBasicInfoList);


	int32_t FuzzyGetTagIDByStr(
		const std::wstring &dbName,
		const std::wstring &str,
		const std::wstring &groupName,
		std::vector<TAGID> &tagIDList);

	int32_t FuzzyGetTagIDByTagName(
		const std::wstring &dbName,
		const std::wstring &tagPartName,
		std::vector<TAGID> &tagIDList, 
		std::vector <std::wstring> &tagNameList,
		std::vector <std::wstring> &tagDescriptionList);

	int32_t FuzzyGetTagIDByTagNameEx(
		const std::wstring &dbName,
		const std::wstring &tagPartName,
		const std::wstring &groupName,
		std::vector<TAGID> &tagIDList);

	int32_t FuzzyGetTagIDByTagName(
		const std::wstring &tagPartName, 
		std::vector<TAGID> &tagIDList, 
		std::vector <std::wstring> &tagNameList,
		std::vector <std::wstring> &tagDescriptionList);

	int32_t FuzzyGetTagIDByTagDescription(
		const std::wstring &dbName, 
		const std::wstring &tagPartDescription,
		std::vector<TAGID> &tagIDList, 
		std::vector <std::wstring> &tagNameList,
		std::vector <std::wstring> &tagDescriptionList);

	int32_t FuzzyGetTagIDByTagDescription(
		const std::wstring &tagPartDescription, 
		std::vector<TAGID> &tagIDList, 
		std::vector <std::wstring> &tagNameList, 
		std::vector <std::wstring> &tagDescriptionList);

	int32_t FuzzyGetTagIDByTagDescriptionEx(
		const std::wstring &dbName,
		const std::wstring &tagPartDescription,
		const std::wstring &groupName,
		std::vector<TAGID> &tagIDList);

	// HIS
	int32_t GetValueByTagID(TAGID tagID, FILETIME startTime, FILETIME endTime, 
		std::vector <TagData> &tagDataList);
	int32_t GetDoubleValueByTagID(TAGID tagID, FILETIME startTime, FILETIME endTime,
		std::vector <TagDoubleData> &tagDataList);

	int EnableSpeedUp(int dbID, bool enable);
	int EnableSpeedUp(const std::wstring &dbName, bool enable);

	int GetDBID(const std::wstring &dbName);
	std::wstring GetDBName(int dbID);

	int GetNValues(
		TAGID tagID,
		FILETIME startTime,
		FILETIME endTime,
		uint32_t valueNum,
		std::vector<TagData> &values);

	int GetNValues(
		TAGID tagID,
		FILETIME startTime,
		FILETIME endTime,
		uint32_t valueNum,
		std::vector<TagDoubleData> &values);

	int32_t GetValueByPeriod(
		TAGID tagID,
		FILETIME startTime,
		FILETIME endTime,
		int64_t period,
		int64_t mode,
		std::vector<TagData> &tagDatas);

	int32_t GetValueByPeriod(
		TAGID tagID,
		FILETIME startTime,
		FILETIME endTime,
		int64_t period,
		std::vector<TagData> &tagDatas);

	int32_t GetValueByPeriod(
		TAGID tagID,
		FILETIME startTime,
		FILETIME endTime,
		int64_t period,
		std::vector<TagDoubleData> &tagDatas);

	int32_t GetValueByTagIDEx( TAGID tagID, FILETIME startTime, FILETIME endTime, 
		std::vector <TagDataEx> &tagDataList);

	int32_t GetValueByTagIDAtTime(TAGID tagID, FILETIME timestamp, int32_t mode, TagData &tagData);
	int32_t GetValueByTagIDAtTime(TAGID tagID, FILETIME timestamp, int32_t mode, TagDoubleData &tagData);

	int32_t GetValuesByTagIDsAtTime(const std::vector<TAGID> &tagIDs, FILETIME timestamp, int32_t mode, std::vector<TagData> &tagDatas,std::vector<int32_t> &results);

	int32_t GetValueByTagIDByStatistics(TAGID tagID, FILETIME startTime, FILETIME endTime,
		int64_t period, int32_t mode, std::vector <TagData> &tagDataList);

	int32_t UpdateValueByTagID(TAGID tagID, TagData &tagData);
	int32_t DeleteValueByTagID(TAGID tagID, FILETIME startTime, FILETIME endTime);

	int32_t GetCurveByZone(TAGID tagID, FILETIME startTime, FILETIME endTime, int32_t zone, std::vector <TagData> &tagDataList );

	int32_t SetHistoryValues(
		TAGID tagID,
		const std::vector<TagData> &tagDatas);

	int32_t SetHistoryValues(
		TAGID tagID,
		const std::vector<TagDoubleData> &tagDatas);
private:

	GlobalDBApi_Impl *m_globalApi;
	CRITICAL_SECTION m_threadLock;
	BOOL m_connected = FALSE;
};
#endif 