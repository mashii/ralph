#include "wrapper.h"

#include <unistd.h>
#include <fcntl.h>

#include <string.h>

std::string safe_strerror(int errorno)
{
    static const int buflen =  1024;
    char buf[buflen];

#if (_POSIX_C_SOURCE >= 200112L || _XOPEN_SOURCE >= 600) && ! _GNU_SOURCE
    strerror_r(errorno, buf, buflen);
    const char *p = buf;
#else
    char *p = strerror_r(errorno, buf, buflen);
#endif

    return std::string(p);
}

int set_nonblock(int fd)
{
    int ret = 0;
    do {
        ret = fcntl(fd, F_GETFL);
    } while (unlikely(ret <0 && errno == EINTR));

    if (ret < 0) {
        return -1;
    }

    do {
        ret = fcntl(fd, F_SETFL, ret | O_NONBLOCK | O_NDELAY);
    } while (unlikely(ret <0 && errno == EINTR));

    return ret;
}
