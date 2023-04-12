#pragma once

#include "Shaddock/Core/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Shaddock {


	class Log
	{
	public:
		static void Init();

		static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;

	};
}

#define SD_CORE_INFO(...)		::Shaddock::Log().GetCoreLogger()->info(__VA_ARGS__)
#define SD_CORE_TRACE(...)		::Shaddock::Log().GetCoreLogger()->trace(__VA_ARGS__)
#define SD_CORE_WARN(...)		::Shaddock::Log().GetCoreLogger()->warn(__VA_ARGS__)
#define SD_CORE_ERROR(...)		::Shaddock::Log().GetCoreLogger()->error(__VA_ARGS__)
#define SD_CORE_CRITICAL(...)	::Shaddock::Log().GetCoreLogger()->critical(__VA_ARGS__)


#define SD_INFO(...)			::Shaddock::Log().GetClientLogger()->info(__VA_ARGS__)
#define SD_TRACE(...)			::Shaddock::Log().GetClientLogger()->trace(__VA_ARGS__)
#define SD_WARN(...)			::Shaddock::Log().GetClientLogger()->warn(__VA_ARGS__)
#define SD_ERROR(...)			::Shaddock::Log().GetClientLogger()->error(__VA_ARGS__)
#define SD_CRITICAL(...)			::Shaddock::Log().GetClientLogger()->critical(__VA_ARGS__)
