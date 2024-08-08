#pragma once
#include <stdint.h>
#include <string>


#ifdef _WIN32
#include <WinSock2.h>
#endif // _WIN32


// SystemTime对应Windows中的SystemTime结构
struct SystemTime
{
	uint16_t year;					// 年 从1970~30827
	uint16_t month;					// 月 1~12
	uint16_t day;					// 日 1~31
	uint16_t hour;					// 时 0~23
	uint16_t minute;				// 分 0~59
	uint16_t second;				// 秒 0~59
	uint16_t milliseconds;			// 毫秒 0~999
};

// FileTime对应Windows中的FileTime结构
// 其时间为公园1601年1月1日0时以来到目前为止逝去的时间长度，
// 其单位为100纳秒，即1秒=10^7百纳秒
struct FileTime
{
	uint32_t lowTime;				// 低32位时间
	uint32_t highTime;				// 高32为时间
};

typedef uint8_t			byte_t;

typedef uint32_t           TAGID_T;
typedef TAGID_T *       LP_TAGID_T;

typedef uint32_t            TAGTYPE_T;
typedef TAGTYPE_T *      LP_TAGTYPE_T;

typedef uint64_t          RTDBTIME_T;
typedef RTDBTIME_T *     LP_RTDBTIME_T;
typedef const RTDBTIME_T * LPCRTDBTIME_T;
//using LPCRTDBTIME_T = const RTDBTIME_T *;

typedef int32_t           STATUS_T;
typedef STATUS_T *   LP_STATUS_T;
typedef const STATUS_T * LPCSTATUS_T;
//using LPCSTATUS_T = const STATUS_T *;

typedef int8_t            VALUE_INT8;
typedef VALUE_INT8 *    LP_VALUE_INT8;

typedef int16_t           VALUE_INT16;
typedef VALUE_INT16 *   LP_VALUE_INT16;

typedef int32_t           VALUE_INT32;
typedef VALUE_INT32 *   LP_VALUE_INT32;

typedef int64_t           VALUE_INT64;
typedef VALUE_INT64 *   LP_VALUE_INT64;

typedef float         VALUE_FLT32;
typedef VALUE_FLT32 *   LP_VALUE_FLT32;

typedef double         VALUE_FLT64;
typedef VALUE_FLT64 *   LP_VALUE_FLT64;

namespace port
{
#ifdef  _WIN32 // _WIN32
	typedef wchar_t			char16;
	typedef int32_t			char32;
	typedef std::basic_string<char32> u32string;
	typedef std::wstring	u16string;

	struct Socket
	{
		SOCKET sock;
		Socket()
			: sock(-1)
		{}
	};
#else // linux
	typedef int16_t			char16;
	typedef wchar_t			char32;
	typedef std::wstring u32string;
	typedef std::basic_string<char16> u16string;
	struct Socket
	{
		int sock;
		Socket()
			: sock(-1)
		{}
	};
#endif // _WIN32
} // port
