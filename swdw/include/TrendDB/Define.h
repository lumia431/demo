#ifndef LIRTDB_DEFINE_H
#define LIRTDB_DEFINE_H

// 软授权开关
#define  RTDB_SOFTLIMIT

// 试用版本开关
//#define LIRTDB_LIMIT
//#define LIRTDB_LIMIT_RUNTIME_CONTINUE

#include <Windows.h>
#include <cstdint>
#include <string>
#include <map>

const int RTDB_TAG_NUM(100000);
const int RTDB_GROUP_NUM(200);
const int RTDB_APPLOCK_NUM(2400);
//const INT LIRTDB_SYSTEMLOCK_NUM(LIRTDB_APPLOCK_NUM + LIRTDB_TAG_NUM);

const uint32_t RTDB_CACHE_FILE_MINLEN = 1;
const uint32_t RTDB_CACHE_FILE_MAXLEN = 100;
const uint32_t RTDB_CACHE_MEM_MINLEN = 1;
const uint32_t RTDB_CACHE_MEM_MAXLEN = 16;
const uint32_t RTDB_CACHE_DATA_MINLEN = 1;
const uint32_t RTDB_CACHE_DATA_MAXLEN = 128;
const uint32_t RTDB_CACHE_DATA_MINNUM = 10;

const uint32_t RTDB_CACHE_FILELEN_UNIT = 1024 * 1024;
const uint32_t RTDB_CACHE_MEMLEN_UNIT = 64 * 1024;
const uint32_t RTDB_CACHE_DATALEN_UNIT = 512;

const uint32_t RTDB_CACHE_SYNCFILE_MAXLEN = 64 * 1024;
const uint32_t RTDB_CACHE_SYNCTAG_MAXCNT = 10000;

const uint32_t MAXLEN_DBNAME = 32;
const uint32_t MAXLEN_GROUP = 60;
const uint32_t MAXLEN_TAGNAME = 120;
const uint32_t MAXLEN_TAGDESC = 200;
const uint32_t MAXLEN_TAGUNIT = 20;
const uint32_t MAXLEN_TAGTYPE = 1;
const uint32_t MAXLEN_TAGSOURCE = 20;
const uint32_t MAXLEN_TAGDESCEX = 99;
const uint32_t MAXLEN_TAGEXA = 49;
const uint32_t MAXLEN_TAGEXB = 49;
const uint32_t MAXLEN_TAGSCRIPT = 3072;

LPCWSTR const RTDB_SERVICE_MUTEX_NAME(L"Global\\LUCULENT_LIRTDB_SYSTEM_RUN_STATUS");
LPCWSTR const RTDB_VERSION_FILENAME(L"version.dat");
LPCWSTR const RTDB_HISTEXE_FILENAME(L"TrendDB_HIS.exe");
LPCWSTR const RTDB_DATAEXE_FILENAME(L"TrendDB_FUN.exe");
LPCWSTR const RTDB_MAINEXE_FILENAME(L"TrendDB_MAIN.exe");
LPCWSTR const RTDB_BACKUPEXE_FILENAME(L"TrendDB_Backup.exe");
LPCWSTR const RTDB_COMINTERFACE_FILENAME(L"TrendDBACCESS.dll");

const std::string RTDB_FILENAME_DBCFG = "TrendDB.ini";
const std::string RTDB_FILENAME_SYSCFG = "DBConfig.ini";

LPCWSTR const RTDB_SHMEM_NAME_SYSCONFIG(L"Global\\LUCULENT_RTDB_SYSCONFIG");
LPCWSTR const RTDB_SHMEM_NAME_SYSSTATUS(L"Global\\LUCULENT_RTDB_SYSSTATUS");
LPCWSTR const RTDB_SHMEM_NAME_GRPCONFIG(L"Global\\LUCULENT_RTDB_GROUPCONFIG");
LPCWSTR const RTDB_SHMEM_NAME_TAGCONFIG(L"Global\\LUCULENT_RTDB_TAGCONFIG");
LPCWSTR const RTDB_SHMEM_NAME_TAGCONFIGEX(L"Global\\LUCULENT_RTDB_TAGCONFIGEX");
LPCWSTR const RTDB_SHMEM_NAME_TAGHASH(L"Global\\LUCULENT_RTDB_TAGHASH");
LPCWSTR const RTDB_SHMEM_NAME_CACHEINDEX(L"Global\\LUCULENT_RTDB_CACHEINDEX");
LPCWSTR const RTDB_SHMEM_NAME_CACHESYNC(L"Global\\LUCULENT_RTDB_CACHESYNC");
LPCWSTR const RTDB_SHMEM_NAME_ALARM(L"Global\\LUCULENT_RTDB_ALARM");
LPCWSTR const RTDB_SHMEM_NAME_FIXCACHE(L"Global\\LUCULENT_RTDB_FIXCACHE");
LPCWSTR const RTDB_SHMEM_NAME_MIGRATIONCONFIG(L"Global\\LUCULENT_RTDB_MIGRATIONCONFIG");
LPCWSTR const RTDB_SHMEM_NAME_MIGRATIONSTATUS(L"Global\\LUCULENT_RTDB_MIGRATIONSTATUS");

LPCWSTR const RTDB_FILE_NAME_SYSCONFIG(L"BaseInfo.dat");
LPCWSTR const RTDB_FILE_NAME_GRPCONFIG(L"GroupInfo.dat");
LPCWSTR const RTDB_FILE_NAME_TAGCONFIG(L"PointInfo.dat");
LPCWSTR const RTDB_FILE_NAME_TAGCONFIGEX(L"PointInfoEx.dat");
LPCWSTR const RTDB_FILE_NAME_TAGHASH(L"TagHash.dat");
LPCWSTR const RTDB_FILE_NAME_CACHEINDEX(L"CacheIndex.dat");
LPCWSTR const RTDB_FILE_NAME_CACHESYNC(L"CacheSync.dat");
LPCWSTR const RTDB_FILE_NAME_ALARM(L"alarm.dat");
LPCWSTR const RTDB_FILE_NAME_FIXCACHE(L"FixCache.dat");
LPCWSTR const RTDB_FILE_NAME_BACKUPSTATUS(L"MigrationStatus.dat");

LPCWSTR const RTDB_MUTEX_NAME_GRPCONFIG(L"Global\\LUCULENT_RTDB_GROUPCONFIG_MUTEX");
LPCWSTR const RTDB_MUTEX_NAME_TAGCONFIG(L"Global\\LUCULENT_RTDB_TAGCONFIG_MUTEX");
LPCWSTR const RTDB_MUTEX_NAME_BACKUPCONFIG(L"Global\\LUCULENT_RTDB_BACKUPCONFIG_MUTEX");
LPCWSTR const RTDB_MUTEX_NAME_CACHEOPEN(L"Global\\LUCULENT_RTDB_CACHEOPEN_MUTEX");
LPCWSTR const RTDB_MUTEX_NAME_COMOPEN(L"Global\\LUCULENT_RTDB_COMOPEN_MUTEX");

LPCWSTR const RTDB_OBJECT_NAME_SYSTEMLOCK(L"Global\\SystemLock");
LPCWSTR const RTDB_FILE_NAME_SYSTEMLOCK(L"SystemLock");

LPCWSTR const RTDB_SEM_HISTCONTROL(L"Global\\LUCULENT_RTDB_HISTCONTROL");
LPCWSTR const RTDB_SEM_DATACONTROL(L"Global\\LUCULENT_RTDB_DATACONTROL");
LPCWSTR const RTDB_SEM_BACKUPCONTROL(L"Global\\LUCULENT_RTDB_BACKUPCONTROL");
const static std::wstring RTDB_FUN_INIT_OVER_EVENT = L"Global\\Luculent.SIS.RTDB.Fun.Init.Over.Event.";
const static std::wstring DBSHAREDINFO = L"SharedInfo.dat";

enum RTDB_SYSTEMLOCK_ID
{
    RTDB_SYSTEMLOCK_TAGHASH = 0,
    RTDB_SYSTEMLOCK_TAGCACHE,
};

enum RTDB_SYS_RUN_STATUS
{
    RTDB_SYS_STOP = 0,
    RTDB_SYS_RUN = 1,
	RTDB_SYS_UNKNOWN
};

enum RTDB_TAG_TYPE
{
    RTDB_TAG_TYPE_BEGIN = '0',
    RTDB_TAG_SWITCH_CHAR = RTDB_TAG_TYPE_BEGIN,
    RTDB_TAG_SWITCH_SHORT,
    RTDB_TAG_SWITCH_INT,
    RTDB_TAG_SWITCH_LONG,
    RTDB_TAG_SWITCH_FLOAT,
    RTDB_TAG_SWITCH_DOUBLE,
    RTDB_TAG_SWITCH_VCHAR,
    RTDB_TAG_SWITCH = RTDB_TAG_SWITCH_VCHAR,
    RTDB_TAG_SIMULATE_FLOAT,
    RTDB_TAG_SIMULATE_DOUBLE,
    RTDB_TAG_SIMULATE = RTDB_TAG_SIMULATE_DOUBLE,
    RTDB_TAG_TYPE_CNT
};

enum RTDB_TAG_STATUS
{
	RTDB_TAG_STATUS_NULL = 0,
	RTDB_TAG_STATUS_NORMAL,
	RTDB_TAG_STATUS_DEL
};

const uint32_t RTDB_SYNCTAG_MAXNUM = 10000;

enum RTDB_HIST_STORE
{
    RTDB_HIST_NONE = 0,
    RTDB_HIST_LSC,
    RTDB_HIST_RESERVE,
    RTDB_HIST_ORG
};

enum RTDB_FIX_STATUS
{
    RTDB_FIX_INIT = 0,
    RTDB_FIX_OK,
    RTDB_FIX_NOT,
    RTDB_FIXING
};

enum RTDB_VALUETYPE    //值类型
{
	RTDB_TYPE_INT = 0,
	RTDB_TYPE_FLOAT,
	RTDB_TYPE_LONG,
	RTDB_TYPE_BOOL,
	RTDB_TYPE_STRING,
	RTDB_TYPE_UNDEFINE
};


struct CacheSyncFile
{
    uint32_t runStatus;
    int runTime;
    uint32_t syncCode;
    uint32_t syncTagCnt;
	uint32_t ctrlCode;
	int ctrlTime;

	int	licenseTagNum;		// 授权点数
	int	tagDelCount;	    // 当前删除点个数
	int	tagCount;		    // 当前有效点个数

	int dbLinkNum;

	int hisProcessID;
	int mainProcessID;
	int funProcessID;
	int calcProcessID;

	int hisCPUUserate;
	int mainCPUUserate;
	int funCPUUserate;
	int calcCPUUserate;

	int hisDisIO;
	int mainDisIO;
	int funDisIO;
	int calcDisIO;

	int hisNetIO;
	int mainNetIO;
	int funNetIO;
	int calcNetIO;

	int hisPrivateMem;
	int mainPrivateMem;
	int funPrivateMem;
	int calcPrivateMem;

	int hisVirtualMem;
	int mainVirtualMem;
	int funVirtualMem;
	int calcVirtualMem;
};

struct CacheSync
{
    CacheSyncFile *syncInfo;
    int *tagId;

    CacheSync():syncInfo(NULL),tagId(NULL) {}
    CacheSync(CacheSyncFile *sync, int *tag):syncInfo(sync),tagId(tag) {}
};

//程序配置内存块
struct PromConfig
{
	int				licenseTagNum;		// 授权点数
	int				licenseDate;		// 授权日期
	BOOL			validLicense;		// 授权有效
	int				tagDelCount;	    // 当前删除点个数
    int				tagCount;		    // 当前有效点个数
    int				minUnusedID;		// 当前最小可用ID号
    int             calcChanged;        // 计算点修改标志
    int             histNotify;         // 历史服务通知
    int             minDeleteID;
    int             reserve0;           // 数据服务通知
    int             reserve1;           // 备份服务通知
    char            version[64];        // 版本信息
};

enum RTDB_MODULE
{
    RTDB_MAINSERVER = 0,
    RTDB_HISTORYSERVER,
    RTDB_BACKUPSERVER,
    RTDB_DATAENGINE,
    RTDB_COMINTERFACE,
	RTDB_CALCSERVER,
    RTDB_MODULE_COUNT,
};

LPCSTR const RTDB_MODULE_NAME[] =
{
    "主服务",
    "历史服务",
    "备份服务",
    "数据引擎",
    "组件接口",
	"计算引擎"
};

//模板版本信息
struct ModuleInfo
{
    char            version[16];        // 版本信息
    char            createTime[16];     // 构建时间
};

//程序状态内存块
struct ServerStatus
{
    int             serverRunTime;      // 服务启动时间
    int             historyServerStatus;// 历史服务状态
    int             historyServerTime;  // 历史服务最新时间
	int				hisProcessID;		// 历史服务进程ID
    int             backupServerStatus; // 备份服务状态
    int             backupServerTime;   // 备份服务最新时间
	int				backupProcessID;	// 历史服务进程ID
	int             dataServerStatus;	// 数据服务状态
	int             dataServerTime;		// 数据服务最新时间
	int				dataProcessID;		// 历史服务进程ID
	int             calcServerStatus;	// 计算服务状态
	int             calcServerTime;		// 计算法服务最新时间
	int				calcProcessID;		// 历史服务进程ID
    ModuleInfo      moduleInfo[RTDB_MODULE_COUNT];  // 模块信息
    int             linkCount;          // 连接数
    
};

//点组
struct TagGroup
{  
    int            gID;                 // 组ID
    char           groupname[MAXLEN_GROUP+1];       // 组名
    unsigned char  availability;        // 组有效
    char           groupdesc[63];       // 组描述
};

//点属性
union AlarmFlag
{
    struct 
    {
        short           sAlarmH:1;
        short           sAlarmSH:1;
        short           sAlarmSSH:1;
        short           sAlarmL:1;
        short           sAlarmSL:1;
        short           sAlarmSSL:1;
        short           sAlarmReserve:9;
        short           sAlarm:1;
    };
    short sflag;
};

enum class AlarmLevel
{
	HIGHT_ALARMLEVEL,
	SHIGHT_ALARMLEVEL,
	SSHIGHT_ALARMLEVEL,
	LOW_ALARMLEVEL,
	SLOW_ALARMLEVEL,
	SSLOW_ALARMLEVEL,
	NUM_ALARMLEVEL
};

struct AlarmAttr
{
    char            cType[3];
    union
    {
        float       fAlarm[3];          // 0-报警 1-超报警 2-超超报警
        int         iAlarm[3];
    };
};

struct TagAttr
{
	int				iID;			    // 点ID
	char			cName[MAXLEN_TAGNAME+1];		    // 点名
	char			cDesc[MAXLEN_TAGDESC+1];		    // 描述
	char			cUints[MAXLEN_TAGUNIT+1];         // 工程单位
	char			cSource[MAXLEN_TAGSOURCE+1];		    // 点源
	char			cExDesc[MAXLEN_TAGDESCEX+1];		// 额外解释
	char			cType[MAXLEN_TAGTYPE+1];			// 类型
	float           fCompdev;		    // 压缩精度
	

	//报警属性
    AlarmFlag       tAlarmFlag;         // 报警标识
    AlarmAttr       tAlarmHigh;         // 高限报警
    AlarmAttr       tAlarmLow;          // 低限报警

	char			cExa[MAXLEN_TAGEXA+1];
	char			cExb[MAXLEN_TAGEXB+1];
	char			cGroupID[MAXLEN_GROUP+1];		// 组ID
	short		    iStatus;			// 点状态
    short           iTimeDes;           // 时间精度
	int				iIsHis;				// 是否需要历史存储
    char            cQuote;             // 是否被引用 0-未引用 1-报警引用
	RTDB_VALUETYPE	tagValueType;			//点值类型
	char			reserve[196];		// 保留200个字节
};

struct TagAttrEx
{
    int            createTime;           // 点创建时间
    int             preIndex;
    int             nextIndex;
    int             reserve;
};

//报警

struct AlarmBuffer
{
    float mmValue;
    int timestamp;
    short timemsec;
    char alarmStatus;
};


#pragma pack(1)
struct AlarmIO
{
    short length;
	int alarmTime;
    short alarmTimemsec;
    char alarmStatus;
	int timestamp;
    short timemsec;
    float mmValue;
    char preAlarmStatus;
    char tagName[50];
};
#pragma pack()

// fix
struct TagFixDeter 
{
    int status;
	int cycle;
	int allCnt;
	int storeCnt;
	int startTime;
};


// backup
enum RTDB_MIGRATE_MODE
{
    RTDB_MIGRATE_RECOVER = 0,
    RTDBA_MIGRATE_MANUALBACKUP,
    RTDB_MIGRATE_AUTOBACKUP,
    RTDB_MIGRATE_MODE_COUNT,
};

enum RTDB_MIGRATE_SYNC
{
    RTDB_MIGRATE_SYNC_OK = 0,
    RTDB_MIGRATE_SYNC_SET
};

enum RTDB_MIGRATE_PLAN
{
    RTDB_MIGRATE_DAY = 0,
    RTDBA_MIGRATE_WEEK,
    RTDB_MIGRATE_MONTH,
};

enum RTDB_MIGRATE_STATUS
{
    RTDB_MIGRATE_IDLE = 0,
    RTDB_MIGRATE_REQUEST,
    RTDB_MIGRATE_BUSY,
};

#pragma pack(4)
struct MigrationConfig
{
    int         syncFlag;
    char        dataDir[MAX_PATH];
    char        backupDir[MAX_PATH];
    int         autoBackup;             // 是否自动备份
    int         autoBackupTime;         // 备份时间
    int         autoBackupPlan;         // 备份计划：0－按天 1－按星期 2－按月
    int         autoBackupPlanData;     // 备份计划值
    int         autoBackupDeleteFile;   // 自动备份是否删除原文件
};

struct MigrationStatus
{
    int         status;                 // 状态：0-空闲 1-请求 2-处理中
	int			autoBackupEndTime;		// 备份数据截止时间
    int         migrationCheckTime;     // 备份检查时间
    int         migrationStartTime;     // 备份开始时间
    int         migrationEndTime;       // 备份结束时间
    int         dataStartTime;          // 备份数据开始时间
    int         dataEndTime;            // 备份数据结束时间
    int         dataSize;               // 数据大小（单位：M）
    int         currDataSize;           // 已备份数据大小（单位：M）
    int         progress;               // 进度（百分比）
    int         code;                   // 备份结果
};
#pragma pack()

// 文件信息结构
struct PathNameInfo
{
    std::string path;       // 文件路径
    std::string namePre;    // 文件名前缀
    std::string nameSuf;    // 文件名后缀
};

#endif // LIRTDB_DEFINE_H
