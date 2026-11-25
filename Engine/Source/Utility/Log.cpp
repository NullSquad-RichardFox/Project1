#include "pch.h"
#include "Log.h"


void Logger::Initialize()
{
	ASSERT(sLoggerInstance == nullptr, "Logger already initialized!");
	sLoggerInstance = new Logger();

	std::filesystem::path path = "Log/global.log";
	std::filesystem::create_directories(path.parent_path());
	sLoggerInstance->LogFile.open(path);

	sLoggerInstance->AddLogCategory("core");
	sLoggerInstance->AddLogCategory("assert");
}

void Logger::Shutdown()
{
	ASSERT(sLoggerInstance, "Logger doesn't exist!");

	sLoggerInstance->LogFile.close();
	for (auto& [cat, file] : sLoggerInstance->AllCategories)
	{
		file.close();
	}

	delete sLoggerInstance;
	sLoggerInstance = nullptr;
}

void Logger::AddLogCategory(const std::string& category)
{
	std::filesystem::path path = std::format("Log/{}.log", category);
	AllCategories[category].open(path);
}

void Logger::DisableLogCategory(const std::string& category)
{
	DisabledCategories.insert(category);
}

void Logger::EnableLogCategory(const std::string& category)
{
	if (!DisabledCategories.contains(category))
		return;

	DisabledCategories.erase(category);
}

void Logger::EnableOnlyCategory(const std::string& category)
{
	for (const auto& [cat, file] : AllCategories)
	{
		if (cat == category)
			continue;

		DisabledCategories.insert(cat);
	}
}

void Logger::MinFlushLevel(ELogLevel level)
{
	MinLogLevel = level;
}

void Logger::LogMessage_Int(ELogLevel level, const std::string& category, const std::string& fmessage)
{
	ASSERT(sLoggerInstance != nullptr, "Logger uninitialized!");
	ASSERT(AllCategories.contains(category), "Unknown category!");
	ASSERT(AllCategories[category].is_open() && LogFile.is_open(), "Log files uninitialized!");

	auto time = std::chrono::current_zone()->to_local(std::chrono::system_clock::now());
	std::string prefix = std::format("[{:%H:%M:%S}][{}]", time, category);

	if ((int32)level < (int32)MinLogLevel)
		return;

	switch (level)
	{
	case ELogLevel::Display:
		std::cout << "\033[90m";
		break;

	case ELogLevel::Info:
		std::cout << "\033[92m";
		break;

	case ELogLevel::Warning:
		std::cout << "\033[93m";
		break;

	case ELogLevel::Error:
		std::cout << "\033[91m";
		break;

	case ELogLevel::Critical:
		std::cout << "\033[97m\033[41m";
		break;
	}

	std::cout << prefix << ": " << fmessage << "\n";
	std::cout << "\033[0m";

	switch (level)
	{
	case ELogLevel::Display:
		prefix += "[Display]: ";
		break;

	case ELogLevel::Info:
		prefix += "[Info]: ";
		break;

	case ELogLevel::Warning:
		prefix += "[Warning]: ";
		break;

	case ELogLevel::Error:
		prefix += "[Error]: ";
		break;

	case ELogLevel::Critical:
		prefix += "[Critical]: ";
		break;
	}

	LogFile << prefix << fmessage << "\n";
	LogFile.flush();

	AllCategories[category] << prefix << fmessage << "\n";
	AllCategories[category].flush();
}
