#pragma once


#ifdef SD_PLATFORM_WINDOWS
	#ifdef SD_BUILD_DLL
		#define SHADDOCK_API __declspec(dllexport)
	#else
		#define SHADDOCK_API __declspec(dllimport)
	#endif

#else
	#error Shaddock only support Windows!
#endif

#define BIT(x) (1 << x)