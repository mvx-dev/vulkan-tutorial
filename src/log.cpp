#include "log.h"

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>

namespace Log {
namespace {
using SyncLogger =
    lwlog::logger<lwlog::default_memory_buffer_limits,
                  lwlog::synchronous_policy, lwlog::default_flush_policy,
                  lwlog::multi_threaded_policy, lwlog::sinks::stdout_sink>;

struct LogMessage {
    std::string loggerName;
    Level level;
    std::string text;
};

// Shared state
std::unordered_map<std::string, std::shared_ptr<SyncLogger>> loggers;
std::queue<LogMessage> queue;
std::mutex queue_mutex;
std::condition_variable cv;
std::atomic<bool> running{false};
std::thread worker;

void worker_function() {
    while (running) {
        std::unique_lock lock(queue_mutex);
        cv.wait(lock, [] { return !queue.empty() || !running; });

        while (!queue.empty()) {
            auto msg = queue.front();
            queue.pop();
            lock.unlock();

            auto it = loggers.find(msg.loggerName);
            if (it != loggers.end()) {
                auto &logger = it->second;
                switch (msg.level) {
                case Level::Debug:
                    logger->debug(msg.text.c_str());
                    break;
                case Level::Info:
                    logger->info(msg.text.c_str());
                    break;
                case Level::Warn:
                    logger->warning(msg.text.c_str());
                    break;
                case Level::Error:
                    logger->error(msg.text.c_str());
                    break;
                case Level::Critical:
                    logger->critical(msg.text.c_str());
                    break;
                }
            }

            lock.lock();
        }
    }
}
} // namespace

void init_global() {
    auto console = std::make_shared<SyncLogger>("CONSOLE");

    console->add_sink(
        std::make_shared<lwlog::sinks::file_sink<
            lwlog::default_memory_buffer_limits, lwlog::default_flush_policy,
            lwlog::multi_threaded_policy>>("./console.log"));

    auto valid = std::make_shared<SyncLogger>("VALIDATION");
    valid->add_sink(
        std::make_shared<lwlog::sinks::file_sink<
            lwlog::default_memory_buffer_limits, lwlog::default_flush_policy,
            lwlog::multi_threaded_policy>>("./validation.log"));

    loggers["console"] = console;
    loggers["valid"] = valid;

    running = true;
    worker = std::thread(worker_function);
}

void push(const std::string &loggerName, Level level, const std::string &msg) {
    {
        std::lock_guard lock(queue_mutex);
        queue.push({loggerName, level, msg});
    }
    cv.notify_one();
}

} // namespace Log
