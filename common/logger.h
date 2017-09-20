#ifndef RALPH_COMMON_LOGGER_H
#define RALPH_COMMON_LOGGER_H

#include <mutex>


namespace ralph
{

class Logger {
public:
    enum Level {
        kLevelFatal   = 0,
        kLevelError   = 1,
        kLevelWarn    = 2,
        kLevelInfo    = 3,
        kLevelDebug   = 4,
        kLevelVerbose = 5,
    };

public:
    // 设置日志级别
    static void SetFilter(Level filter);

    // 日志文件名，如果不设置，默认输出到标准输出
    static bool SetLogFileName(const char * fn);

    // 写日志（单条日志限长2K）
    static void Log(Level level, const char * file, int line,
                    const char * fmt, ...);

private:
    static int _fd;
    static Level _filter;
    static int _max_size;
    static std::mutex _lock;
};

} /* namespace ralph */


#define LogFatal(fmt, args...)   ralph::Logger::Log(ralph::Logger::kLevelFatal  , __FILE__, __LINE__, fmt, ##args)
#define LogError(fmt, args...)   ralph::Logger::Log(ralph::Logger::kLevelError  , __FILE__, __LINE__, fmt, ##args)
#define LogWarn(fmt, args...)    ralph::Logger::Log(ralph::Logger::kLevelWarn   , __FILE__, __LINE__, fmt, ##args)
#define LogInfo(fmt, args...)    ralph::Logger::Log(ralph::Logger::kLevelInfo   , __FILE__, __LINE__, fmt, ##args)
#define LogDebug(fmt, args...)   ralph::Logger::Log(ralph::Logger::kLevelDebug  , __FILE__, __LINE__, fmt, ##args)
#define LogVerbose(fmt, args...) ralph::Logger::Log(ralph::Logger::kLevelVerbose, __FILE__, __LINE__, fmt, ##args)


#endif // RALPH_COMMON_LOGGER_H
