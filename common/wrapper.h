#ifndef RALPH_COMMON_WRAPPER_H
#define RALPH_COMMON_WRAPPER_H

#include <sys/uio.h>
#include <unistd.h>

#include <string>

#include "likely.h"

inline ssize_t safe_read(int fd, void *buf, size_t count) {
    ssize_t ret;
    do {
        ret = read(fd, buf, count);
    } while (unlikely(ret < 0 && errno == EINTR));
    return ret;
}

inline ssize_t safe_readv(int fd, struct iovec *iov, int iovcnt) {
    ssize_t ret;
    do {
        ret = readv(fd, iov, iovcnt);
    } while (unlikely(ret < 0 && errno == EINTR));
    return ret;
}

inline ssize_t safe_write(int fd, const void *buf, size_t count)
{
    ssize_t ret;
    do {
        ret = write(fd, buf, count);
    } while (unlikely(ret < 0 && errno == EINTR));
    return ret;
}

inline ssize_t safe_writev(int fd, struct iovec *iov, int iovcnt) {
    ssize_t ret;
    do {
        ret = writev(fd, iov, iovcnt);
    } while (unlikely(ret < 0 && errno == EINTR));
    return ret;
}

inline int safe_close(int fd)
{
    int ret;
    do {
        ret = close(fd);
    } while (unlikely(ret < 0 && errno == EINTR));
    return ret;
}

std::string safe_strerror(int errorno);

int set_nonblock(int fd);

#endif // RALPH_COMMON_WRAPPER_H

