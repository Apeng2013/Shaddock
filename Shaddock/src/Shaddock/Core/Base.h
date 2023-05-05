#pragma once

#include <memory>

#include "Shaddock/Core/PlatformDetection.h"

#ifdef SD_DEBUG
	#if defined(SD_PLATFORM_WINDOWS)
		#define SD_DEBUGBREAK() __debugbreak();
	#elif defined(SD_PLATFORM_LINUX)
		#include <signal.h>
		#define SD_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define SD_ENABLE_ASSERTS
#endif

#ifdef SD_ENABLE_ASSERTS
	#define SD_ASSERT(x, ...) { if(!(x)) {SD_ERROR("Assertion Failed: {0}", __VA_ARGS__); SD_DEBUGBREAK();}}
	#define SD_CORE_ASSERT(x, ...) { if(!(x)) {SD_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); SD_DEBUGBREAK();}}
#else
	#define SD_ASSERT(x, ...)
	#define SD_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define SD_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Shaddock {
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}