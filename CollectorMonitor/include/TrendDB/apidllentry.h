#ifndef LRAPI_DLLENTRY_H
#define LRAPI_DLLENTRY_H

////////////////////////////////////////////////////////////////////////////////
//
// 文件名称：dllentry.h
// 文件标识：
// 摘要：LiRTDBApi模块－dll导入导出
//
// 版本：1.0
// 作者：乐蔚芸
// 日期：2011.3.11
//
////////////////////////////////////////////////////////////////////////////////

#ifndef RTDB_APICLR
#ifdef RTDBAPI_EXPORTS
#define DBAPI_DLLENTRY    __declspec(dllexport)
#else
#define DBAPI_DLLENTRY    __declspec(dllimport)
#endif // LIRTDBAPI_EXPORTS
#endif // LIRTDB_APICLR

#endif // LRAPI_DLLENTRY_H
