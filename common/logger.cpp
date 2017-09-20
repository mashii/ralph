#include "logger.h"

#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "wrapper.h"

namespace ralph
{

//
// 默认输出到标准输出
//
int Logger::_fd = STDOUT_FILENO;

//
// 单条日志限长2K
//
int Logger::_max_size = 2048;

//
// 默认日志级别为Debug
//
Logger::Level Logger::_filter = Logger::kLevelDebug;

std::mutex Logger::_lock;

void Logger::SetFilter(Level filter)
{
    _filter = filter;
}

//
// 设置输出日志到文件
// 文件描述符等待进程结束自动关闭
//
bool Logger::SetLogFileName(const char * fn)
{
    _fd = open(fn, O_CREAT | O_APPEND | O_WRONLY | O_NOFOLLOW | O_NOCTTY, S_IRUSR |
                   S_IWUSR | S_IRGRP  | S_IWGRP  | S_IROTH    | S_IWOTH);
    if (_fd < 0) {
        fprintf(stderr, "open log file failed, %s\n", safe_strerror(errno).c_str());
        return false;
    }
    return true;
}

void Logger::Log(Level level, const char * file, int line, const char * fmt, ...)
{
    if (level > _filter)
        return;

    const size_t size = static_cast<size_t>( _max_size) + 256;
    char buf[size];
    char * ptr = buf;

    //
    // 输出日志级别
    //
    size_t wsize = 6;
    switch (level) {
        case kLevelError  : memcpy(ptr, "ERROR ", wsize); ptr = buf + wsize; break;
        case kLevelWarn   : memcpy(ptr, "WARN  ", wsize); ptr = buf + wsize; break;
        case kLevelFatal  : memcpy(ptr, "FATAL ", wsize); ptr = buf + wsize; break;
        case kLevelInfo   : memcpy(ptr, "INFO  ", wsize); ptr = buf + wsize; break;
        case kLevelDebug  : memcpy(ptr, "DEBUG ", wsize); ptr = buf + wsize; break;
        case kLevelVerbose: memcpy(ptr, "VERB  ", wsize); ptr = buf + wsize; break;
        default     : memcpy(ptr, "OTHER ", wsize); ptr = buf + wsize; break;
    }

    //
    // 输出当前时间
    //
    timeval now;
    gettimeofday(&now, nullptr);
    struct tm tm;
    localtime_r(&now.tv_sec, &tm);
    wsize += static_cast<size_t>(snprintf(ptr, static_cast<size_t>(size-wsize),
                                          "%02d-%02d %02d:%02d:%02d.%06ld ",
                                          tm.tm_mon + 1, tm.tm_mday, tm.tm_hour,
                                          tm.tm_min, tm.tm_sec, now.tv_usec));
    ptr = buf + wsize;

    //
    // 输出日志，超过2K则截断
    //
    va_list ap;
    va_start(ap, fmt);
    int tmp = vsnprintf(ptr, static_cast<size_t>(_max_size), fmt, ap);
    va_end(ap);

    wsize += static_cast<size_t>(tmp > _max_size ? _max_size : tmp);
    ptr = buf + wsize;

    //
    // 输出日志所在文件及行
    //
    wsize += static_cast<size_t>(snprintf(ptr, static_cast<size_t>(size-wsize),
                                          " [%s:%d]\n", file, line));

    std::lock_guard<std::mutex> lock_guard(_lock);
    write(_fd, buf, wsize);
}

} /* namespace ralph */
