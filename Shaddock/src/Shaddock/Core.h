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

#ifdef SD_ENABLE_ASSERTS
	#define SD_ASSERT(x, ...) { if(!(x)) {SD_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
	#define SD_CORE_ASSERT(x, ...) { if(!(x)) {SD_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define SD_ASSERT(x, ...)
	#define SD_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)