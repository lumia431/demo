#pragma once
#include <algorithm>
#include <iterator>

namespace RTDB
{
    namespace ApiCpp
    {
        class Utility;
    }
}

class DBAPI_DLLENTRY RTDB::ApiCpp::Utility
{
public:
    Utility(void);
    ~Utility(void);

    static int32_t GetServerTime(int32_t connecter, UINT32 &serverTime);
    static int32_t GetServerVersion(int32_t connecter, ServerInfo &info);
	
	template <typename T>
	static auto SplitVector(const std::vector<T> &vec, uint32_t number = 100) -> std::vector<std::vector<T>>
	{
		std::vector<std::vector<T>> results;
		auto slices = vec.size() / number;
		uint32_t notCompleteSlice = 0;
		notCompleteSlice = vec.size() % number;
		results.reserve(slices + 1);

		std::vector<T> tmpVec;
		auto srcBeg = vec.cbegin();
		auto insertTmpVec = [&](uint32_t num)
		{
			tmpVec.reserve(num);
			std::copy_n(srcBeg, num, std::back_inserter(tmpVec));
			results.push_back(std::move(tmpVec));
			srcBeg += num;
		};

		for (uint32_t i = 0; i < slices; ++i)
		{
			insertTmpVec(number);
		}

		if (notCompleteSlice != 0)
		{
			insertTmpVec(notCompleteSlice);
		}

		return results;
	}

	static auto SplitTimeRange(const FILETIME &sttime, const FILETIME &edtime)->std::vector<std::pair<FILETIME, FILETIME>>;

	static auto SplitTimePeriod(const FILETIME &sttime, const FILETIME &edtime, int64_t period)->std::vector<std::pair<FILETIME, FILETIME>>;

	using TagDatasItr = std::vector<TagData>::const_iterator;
	using TagDoubleDatasItr = std::vector<TagDoubleData>::const_iterator;
	static auto SplitTagDatas(
		const std::vector<TagData> &tagDatas, 
		const FILETIME &sttime, 
		const FILETIME &edtime, 
		int64_t timePeriod,
		std::vector<uint64_t> &tagTimes) -> std::vector<std::pair<TagDatasItr, TagDatasItr>>;

	static auto SplitTagDatas(const TagDatasItr &begItr, const TagDatasItr &endItr, const uint64_t tagTime) ->std::vector<std::pair<TagDatasItr, TagDatasItr>>;

	static auto SplitTagDoubleDatas(
		const std::vector<TagDoubleData> &tagDatas,
		const FILETIME &sttime,
		const FILETIME &edtime,
		int64_t timePeriod,
		std::vector<uint64_t> &tagTimes)->std::vector<std::pair<TagDoubleDatasItr, TagDoubleDatasItr>>;

	static auto SplitTagDoubleDatas(const TagDoubleDatasItr &begItr, const TagDoubleDatasItr &endItr, const uint64_t tagTime)->std::vector<std::pair<TagDoubleDatasItr, TagDoubleDatasItr>>;

};

