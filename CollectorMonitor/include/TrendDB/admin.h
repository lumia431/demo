#pragma once

namespace RTDB
{
    namespace ApiCpp
    {
        class Admin;
    }
}

class DBAPI_DLLENTRY RTDB::ApiCpp::Admin
{
public:
    static int32_t AddGroup(int32_t connecter, const std::vector <GroupInfo> &groupInfoList, std::vector <int32_t> &resultList);
    static int32_t DeleteGroup(int32_t connecter, const std::vector <GroupInfo> &groupInfoList, std::vector <int32_t> &resultList);

    static int32_t AddTag(int32_t connecter, const std::vector <TagInfo> &tagInfoList, std::vector <int32_t> &resultList);
    static int32_t AlterTag(int32_t connecter, const std::vector <TagInfo> &tagInfoList, std::vector <int32_t> &resultList);

    static int32_t DeleteTagToRecycleBin(int32_t connecter, const std::vector <int32_t> &tagIDList, std::vector <int32_t> &resultList);
    static int32_t RestoreTagFromRecycleBin(int32_t connecter, const std::vector <int32_t> &tagIDList, std::vector <int32_t> &resultList);
    static int32_t DeleteTagFromRecycleBin(int32_t connecter, const std::vector <int32_t> &tagIDList, std::vector <int32_t> &resultList);
    static int32_t CompletelyDeleteTag(int32_t connecter, const std::vector <int32_t> &tagIDList, std::vector <int32_t> &resultList);
};
