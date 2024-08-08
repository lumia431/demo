#pragma once

#ifdef _WIN32	// _WIN32
#	ifdef EXPORTS_TRENDDB
#		define API		__declspec(dllexport)
#		define HIDEEN
#	else
#		define API		__declspec(dllimport)
#	endif // EXPORTS_TRENDDB
#	ifndef STDCALL
#		define STDCALL		__stdcall
#	endif
#	ifndef CDECL
#		define CDECL		__cdecl
#	endif // !CDECL


#else // linux
#	ifdef EXPORTS_TRENDDB
#		define API		 __attribute__((visibility("default")))
#		define HIDEEN	 __attribute__((visibility("hidden")))
#	else
#		define API
#	endif // EXPORTS_TRENDDB
#	define STDCALL		__attribute__((__stdcall__))
#	define CDECL		__attribute__(( __cdecl__))
#endif // _WIN32
