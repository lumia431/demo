#pragma once


#ifdef _DLL_EXPORTS
#define DLL_API _declspec(dllexport)
#else
#define DLL_API _declspec(dllimport)
#endif
struct POINT_VALUE
{
	std::string tagName;
	double value;
};
class OpcuaApi
{
public:
	virtual void newOpcuaServer(int port, std::vector<POINT_VALUE> val) = 0;
	virtual void writeNewData(std::vector<POINT_VALUE> val) = 0;
	virtual void status() = 0;
};
extern "C" DLL_API OpcuaApi *GetOpcua();


