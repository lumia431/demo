#pragma once

namespace RTDB
{
    namespace ApiCpp
    {
        class Manage;
    }
}

class DBAPI_DLLENTRY RTDB::ApiCpp::Manage
{
public:
    Manage(void);
    ~Manage(void);

    static int32_t Connect(const std::wstring &address, int32_t port, const std::wstring &user = L"", const std::wstring &pwd = L"");
    static int32_t Disconnect(int32_t connecter);

	static BOOL Connected(int32_t connecter);
};
