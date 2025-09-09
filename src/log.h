#pragma once

#include "lwlog/buffer_limits.h"
#include "lwlog/lwlog.h"
#include "lwlog/policy/log_policy.h"
#include "lwlog/policy/threading_policy.h"
#include "lwlog/sinks/stdout_sink.h"

// Alias for logger with defaults + stdout sink

namespace Log {

using BaseLogger =
    lwlog::logger<lwlog::default_memory_buffer_limits,
                  lwlog::synchronous_policy, lwlog::default_flush_policy,
                  lwlog::single_threaded_policy, lwlog::sinks::stdout_sink>;

inline std::shared_ptr<BaseLogger> &ConsoleLogger() {
    static auto instance = std::make_shared<BaseLogger>("CONSOLE");
    return instance;
}

inline std::shared_ptr<BaseLogger> &ValidationLogger() {
    static auto instance = std::make_shared<BaseLogger>("VALIDATION");
    return instance;
}

inline void init() {

    auto console = ConsoleLogger();
    console->set_pattern("[%T.%e] [:^10%n] .level([:^12%l]) [%$/%!:%#]: %v");
    console->add_sink(
        std::make_shared<lwlog::sinks::file_sink<
            lwlog::default_memory_buffer_limits, lwlog::default_flush_policy,
            lwlog::multi_threaded_policy>>("./console.log"));

    auto validation = ValidationLogger();
    validation->set_pattern("[%T.%e] [:^10%n] .level([:^12%l]) [%$/%!:%#]: %v");
    validation->add_sink(
        std::make_shared<lwlog::sinks::file_sink<
            lwlog::default_memory_buffer_limits, lwlog::default_flush_policy,
            lwlog::multi_threaded_policy>>("./validation.log"));
}

class MultiLogger {
    std::vector<std::shared_ptr<BaseLogger>> loggers;

  public:
    void add_logger(const std::shared_ptr<BaseLogger> &logger) {
        loggers.push_back(logger);
    }

    template <typename... Args> void debug(const Args &...args) {
        for (auto &l : loggers) {
            l->debug(args...);
        }
    }

    template <typename... Args> void info(const Args &...args) {
        for (auto &l : loggers) {
            l->info(args...);
        }
    }

    template <typename... Args> void warning(const Args &...args) {
        for (auto &l : loggers) {
            l->warning(args...);
        }
    }

    template <typename... Args> void error(const Args &...args) {
        for (auto &l : loggers) {
            l->error(args...);
        }
    }

    template <typename... Args> void critical(const Args &...args) {
        for (auto &l : loggers) {
            l->critical(args...);
        }
    }
};

inline MultiLogger &GlobalLogger() {
    static MultiLogger instance;
    return instance;
}

inline void init_global() {
    auto &global = GlobalLogger();
    global.add_logger(ConsoleLogger());
    global.add_logger(ValidationLogger());
}

} // namespace Log

#define LOG_CONSOLE_DEBUG(...) ::Log::ConsoleLogger()->debug(__VA_ARGS__)
#define LOG_CONSOLE_INFO(...) ::Log::ConsoleLogger()->info(__VA_ARGS__)
#define LOG_CONSOlE_WARN(...) ::Log::ConsoleLogger()->warning(__VA_ARGS__)
#define LOG_CONSOLE_ERROR(...) ::Log::ConsoleLogger()->error(__VA_ARGS__)
#define LOG_CONSOLE_CRITICAL(...) ::Log::ConsoleLogger()->critical(__VA_ARGS__)

#define LOG_VALID_DEBUG(...) ::Log::ValidationLogger()->debug(__VA_ARGS__)
#define LOG_VALID_INFO(...) ::Log::ValidationLogger()->info(__VA_ARGS__)
#define LOG_VALID_WARN(...) ::Log::ValidationLogger()->warning(__VA_ARGS__)
#define LOG_VALID_ERROR(...) ::Log::ValidationLogger()->error(__VA_ARGS__)
#define LOG_VALID_CRITICAL(...) ::Log::ValidationLogger()->critical(__VA_ARGS__)

#define LOG_GLOBAL_DEBUG(...) ::Log::GlobalLogger().debug(__VA_ARGS__)
#define LOG_GLOBAL_INFO(...) ::Log::GlobalLogger().info(__VA_ARGS__)
#define LOG_GLOBAL_WARN(...) ::Log::GlobalLogger().warning(__VA_ARGS__)
#define LOG_GLOBAL_ERROR(...) ::Log::GlobalLogger().error(__VA_ARGS__)
#define LOG_GLOBAL_CRITICAL(...) ::Log::GlobalLogger().critical(__VA_ARGS__)
