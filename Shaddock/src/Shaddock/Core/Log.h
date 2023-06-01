#pragma once

#include "Shaddock/Core/Base.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "glm/gtx/string_cast.hpp"

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
template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& vector)
{
	return os << glm::to_string(vector);
}
template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix)
{
	return os << glm::to_string(matrix);
}
template<typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::qua<T, Q>& quaternio)
{
	return os << glm::to_string(quaternio);
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
#define SD_CRITICAL(...)		::Shaddock::Log().GetClientLogger()->critical(__VA_ARGS__)
