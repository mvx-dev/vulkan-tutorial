#pragma once
#include <lwlog/lwlog.h>
#include <string>

namespace Log {
enum class Level { Info, Debug, Warn, Error, Critical };

void init_global();

void push(const std::string &loggerName, Level level, const std::string &msg);
} // namespace Log

#define LOG_CONSOLE_INFO(msg) ::Log::push("console", ::Log::Level::Info, msg)
#define LOG_CONSOLE_DEBUG(msg) ::Log::push("console", ::Log::Level::Debug, msg)
#define LOG_CONSOLE_WARN(msg) ::Log::push("console", ::Log::Level::Warn, msg)
#define LOG_CONSOLE_ERROR(msg) ::Log::push("console", ::Log::Level::Error, msg)
#define LOG_CONSOLE_CRIT(msg)                                                  \
    ::Log::push("console", ::Log::Level::Critical, msg)

#define LOG_VALID_INFO(msg) ::Log::push("valid", ::Log::Level::Info, msg)
#define LOG_VALID_DEBUG(msg) ::Log::push("valid", ::Log::Level::Debug, msg)
#define LOG_VALID_WARN(msg) ::Log::push("valid", ::Log::Level::Warn, msg)
#define LOG_VALID_ERROR(msg) ::Log::push("valid", ::Log::Level::Error, msg)
#define LOG_VALID_CRIT(msg) ::Log::push("valid", ::Log::Level::Critical, msg)
