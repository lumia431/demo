#ifndef COMMTYPES_H
#define COMMTYPES_H
/*
 *	API和整个工程都需要使用这个头文件中的类型，所以将其整合为一个文件
 */
#include <stdint.h>
#include <windef.h>
#include <string>
#include <map>

enum DB_STATTISTICS_SELECT_MODE
{
	DB_STATTISTICS_MAX = 0,  //最大0
	DB_STATTISTICS_MIN,		//最小1
	DB_STATTISTICS_CAVG,	//平均2
	DB_STATTISTICS_WAVG,	//加权平均3
	DB_STATTISTICS_CSUM,	//求和4
	DB_STATTISTICS_WSUM,	//加权求和5
	DB_STATTISTICS_SUB,		//差值6
	DB_STATTISTICS_PERIOD	//插值
};

enum DB_STATTISTICS_MODE
{
	S_MAX = 0x01,			// 最大值
	S_MIN = 0x02,			// 最小值
	S_SUM =	0x04,			// 平均值
	S_AVG = 0x08,			// 和值
	S_SUB = 0x0F,			// 差值
	S_INT = 0x10,			// 插值
	S_WAVG = 0x20,			// 加权平均
	S_WSUM = 0x40,			// 加权和
	S_ALL = 0xff			// 所有模式
};

enum DB_TIME_SELECT_MODE
{
	DB_TIME_NEAR = 0,
	DB_TIME_BEFORE,
	DB_TIME_AFTER,
	DB_TIME_INTER,
	DB_TIME_LAST
};

struct TAGID
{
	int dbID = 0;
	int tagID = 0;

	TAGID() = default;
	TAGID(int _dbID, int _tagID)
		: dbID(_dbID)
		, tagID(_tagID)
	{}
};

struct GroupInfo
{
	std::wstring name;
	GroupInfo() = default;
	GroupInfo(const std::wstring &_name)
		: name(_name)
	{}
};

struct AlarmInfo
{
	int32_t alarm;
	int32_t type;
	float value;
	std::wstring tagName;

	struct AlarmInfo() :
		alarm(0),
		type(0),
		value(0)
	{
	}
};

struct TagBasicInfo
{
	int32_t id;
	TAGID tagID;
	std::wstring name;
	std::wstring dbName;
	std::wstring type;
	std::wstring description;
	std::wstring unit;
	std::wstring source;
	std::wstring group;
	std::wstring extraDescription;
	int32_t createTime;
	int32_t status;

	TagBasicInfo() :
		id(0),
		createTime(0),
		status(0)
	{}

	TagBasicInfo(
		const std::wstring &_name,
		const std::wstring &_type,
		const std::wstring &_group,
		const std::wstring &_dbName)
		: name(_name)
		, type(_type)
		, group(_group)
		, dbName(_dbName)
	{}
};

struct TagInfo : TagBasicInfo
{
	std::wstring extraDescriptionA;
	std::wstring extraDescriptionB;
	int32_t historyFlag;
	float storePrecision;
	int32_t timePrecision;
	//RTDB_VALUETYPE tagValueType;	//点值类型
	AlarmInfo alarm[6];

	TagInfo() = default;
	TagInfo(
		const std::wstring &_name,
		const std::wstring &_type,
		const std::wstring &_group,
		const std::wstring &_dbName,
		int32_t _historyFlag,
		float _storePrecision)
		: TagBasicInfo(_name, _type, _group, _dbName)
		, historyFlag(_historyFlag)
		, storePrecision(_storePrecision)
		//, tagValueType(RTDB_VALUETYPE::RTDB_TYPE_FLOAT)
	{}
};

struct CalculateTagInfo
{
	int32_t id;
	TAGID tagID;
	int32_t cycle;
	int32_t priority;
	std::wstring expression;
};

struct TagData
{
	int32_t status = 1;
	FILETIME timestamp;
	float value;

	friend bool operator< (const TagData &lhs, const TagData &rhs)
	{
		if (lhs.timestamp.dwHighDateTime != rhs.timestamp.dwHighDateTime)
		{
			return lhs.timestamp.dwHighDateTime < rhs.timestamp.dwHighDateTime;
		}
		return lhs.timestamp.dwLowDateTime < rhs.timestamp.dwLowDateTime;
	}

	TagData() :
		status(0),
		value(0)
	{
		timestamp.dwHighDateTime = 0;
		timestamp.dwLowDateTime = 0;
	}
};

struct TagDoubleData
{
	int32_t status = 1;
	FILETIME timestamp;
	double value;

	friend bool operator< (const TagDoubleData &lhs, const TagDoubleData &rhs)
	{
		if (lhs.timestamp.dwHighDateTime != rhs.timestamp.dwHighDateTime)
		{
			return lhs.timestamp.dwHighDateTime < rhs.timestamp.dwHighDateTime;
		}
		return lhs.timestamp.dwLowDateTime < rhs.timestamp.dwLowDateTime;
	}

	TagDoubleData() :
		status(0),
		value(0)
	{
		timestamp.dwHighDateTime = 0;
		timestamp.dwLowDateTime = 0;
	}
};


struct TagDataEx
{
	int32_t status;
	FILETIME timestamp;
	float value;
	int32_t position;
};

struct ServerInfo
{
	std::wstring version;
	std::wstring tagAllCount;
	std::wstring tagUseCount;
	std::wstring tagIdleCount;
};
#endif