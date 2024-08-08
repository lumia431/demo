#ifndef LIRTDBAPI_H
#define LIRTDBAPI_H

#ifndef LIRTDB_APICLR
#include <windows.h>
#include <vector>
#include <stdint.h>
#include "apidllentry.h"
#include "apitypes.h"
#include "commtypes.h"
#include "Manage.h"
#include "Admin.h"
#include "Info.h"
#include "Realtime.h"
#include "History.h"
#include "GlobalDBApi.h"
#include "Utility.h"

// 兼容以前老代码中命名空间
namespace LiRTDB = RTDB;

#endif // LIRTDB_APICLR
#endif // LIRTDBAPI_H
