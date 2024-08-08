#pragma once
#pragma warning(disable:4251)
#ifdef MAKECSV_EXPORTS
#define MAKECSV_EXPORTS __declspec(dllexport)
#else 
#define  MAKECSV_EXPORTS __declspec(dllimport)
#endif // LED_EXPORTS
#include <string>


extern "C" MAKECSV_EXPORTS void CreateCsv(std::string dataStr,std::string path);


