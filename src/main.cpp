
#include "spdlog/spdlog.h"

#include <iostream>
#include <memory>

namespace logger
{
	template <typename... Args>
	void error(const char* fmt, const Args&... args)
	{
		spdlog::apply_all([&](std::shared_ptr<spdlog::logger> l) { l->error(fmt, args...); });
	}

	template <typename... Args>
	void warn(const char* fmt, const Args&... args)
	{
		spdlog::apply_all([&](std::shared_ptr<spdlog::logger> l) { l->warn(fmt, args...); });
	}

	template <typename... Args>
	void info(const char* fmt, const Args&... args)
	{
		spdlog::apply_all([&](std::shared_ptr<spdlog::logger> l) { l->info(fmt, args...); });
	}

	template <typename... Args>
	void debug(const char* fmt, const Args&... args)
	{
		spdlog::apply_all([&](std::shared_ptr<spdlog::logger> l) { l->debug(fmt, args...); });
	}

#ifdef SPDLOG_DEBUG_ON
#define DEBUG(x, ...) logger::debug(x, ##__VA_ARGS__)
#else
#define DEBUG(x, ...)
#endif

	void initialize_console()
	{
		auto console = spdlog::stdout_color_mt("console");
		console->set_pattern("[%H:%M:%S.%e] %v");
#ifdef SPDLOG_DEBUG_ON
		console->set_level(spdlog::level::debug);
#else
		console->set_level(spdlog::level::info);
#endif
	}

	void initialize_file(const spdlog::filename_t filename)
	{
		auto file = spdlog::basic_logger_mt("file", filename);
		file->set_pattern("%Y/%m/%d %H:%M:%S.%e [%L] %v");
#ifdef SPDLOG_DEBUG_ON
		file->set_level(spdlog::level::debug);
#else
		file->set_level(spdlog::level::info);
#endif
	}

	void initialize(const spdlog::filename_t filename)
	{
		initialize_console();
		initialize_file(filename);
	}
}

int main(int, char*[])
{
	logger::initialize("file.log");
		
	DEBUG("This is a detailed Debug message {}, {}", "info", "info");
	logger::info("Trying out spdlog. {}", "Salad");
	logger::warn("This is a warning");
	logger::error("This is error number {}.", 1);

    return 0;
}
