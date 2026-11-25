#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"


enum class ELogLevel
{
	Display,
	Info,
	Warning,
	Error,
	Critical
};

class Logger
{
public:
	static void Initialize();
	static void Shutdown();

	static Logger* GetLogger() { return sLoggerInstance; }

	void AddLogCategory(const std::string& category);
	void DisableLogCategory(const std::string& category);
	void EnableLogCategory(const std::string& category);
	void EnableOnlyCategory(const std::string& category);

	void MinFlushLevel(ELogLevel level);

	template<typename... Args>
	void Log(ELogLevel level, const std::string& category, const std::string& message, Args&&... args)
	{
		LogMessage_Int(level, category, std::vformat(message, std::make_format_args(args...)));
	}

private:
	Logger() = default;

	void LogMessage_Int(ELogLevel level, const std::string& category, const std::string& fmessage);

	inline static Logger* sLoggerInstance = nullptr;

	std::ofstream LogFile;
	ELogLevel MinLogLevel;
	std::unordered_map<std::string, std::ofstream> AllCategories;
	std::unordered_set<std::string> DisabledCategories;
};

template<>
struct std::formatter<glm::vec2>
{
	constexpr auto parse(std::format_parse_context& ctx)
	{
		return ctx.begin();
	}

	auto format(const glm::vec2& vec, std::format_context& ctx) const
	{
		return std::format_to(ctx.out(), "({}, {})", vec.x, vec.y);
	}
};

template<>
struct std::formatter<glm::vec3>
{
	constexpr auto parse(std::format_parse_context& ctx)
	{
		return ctx.begin();
	}

	auto format(const glm::vec3& vec, std::format_context& ctx) const
	{
		return std::format_to(ctx.out(), "({}, {}, {})", vec.x, vec.y, vec.z);
	}
};

template<>
struct std::formatter<glm::vec4>
{
	constexpr auto parse(std::format_parse_context& ctx)
	{
		return ctx.begin();
	}

	auto format(const glm::vec4& vec, std::format_context& ctx) const
	{
		return std::format_to(ctx.out(), "({}, {}, {}, {})", vec.x, vec.y, vec.z, vec.w);
	}
};

#define LOG_DISPLAY(cat, ...) Logger::GetLogger()->Log(ELogLevel::Display, cat, __VA_ARGS__)
#define LOG_INFO(cat, ...) Logger::GetLogger()->Log(ELogLevel::Info, cat, __VA_ARGS__)
#define LOG_WARNING(cat, ...) Logger::GetLogger()->Log(ELogLevel::Warning, cat, __VA_ARGS__)
#define LOG_ERROR(cat, ...) Logger::GetLogger()->Log(ELogLevel::Error, cat, __VA_ARGS__)
#define LOG_CRITICAL(cat, ...) Logger::GetLogger()->Log(ELogLevel::Critical, cat, __VA_ARGS__)

#define LOG(...) LOG_DISPLAY("Core", __VA_ARGS__)

#ifdef CF_DEBUG
#define INTERNAL_ASSERT_IMPL(check, msg, ...) { if (!(check)) { LOG_ERROR("Assert", msg, __VA_ARGS__); __debugbreak(); } }
#define ASSERT(check, msg) INTERNAL_ASSERT_IMPL(check, "Assertion failed: {0}", msg)
#define RAW_ASSERT(check, ...) assert(check)
#else
#define ASSERT(...) 
#define RAW_ASSERT(...) 
#endif

#define DISABLE_LOG_CATEGORY(cat) Logger::GetLogger()->DisableLogCategory(cat);
#define ENABLE_LOG_CATEGORY(cat) Logger::GetLogger()->EnableLogCategory(cat);
#define LOG_ONLY_CATEGORY(cat) Logger::GetLogger()->EnableOnlyCategory(cat);
#define ADD_LOG_CATEGORY(cat) Logger::GetLogger()->AddLogCategory(cat);