#pragma once

#include "Shaddock/Core/PlatformDetection.h"

#include <memory>

#define SD_EXPAND_MACRO(x) x
#define SD_STRINGIFY_MACRO(x) #x

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

#include "Shaddock/Core/Assert.h"

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
