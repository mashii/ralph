#include "acceptor.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <json/value.h>

#include "ralph/common/logger.h"
#include "ralph/common/wrapper.h"

namespace ralph {

Acceptor::Acceptor(const Json::Value & configure)
        : _run(true)
        , _configure(configure)
        , _last_handler(0)
        , _poller(new Poller(static_cast<int>(configure["acceptor][listen"].size())))
{
}

Acceptor::~Acceptor()
{
    for (auto & it : _listener) {
        safe_close(it.fd);
    }
}

bool Acceptor::Initialize()
{
    auto & listen = _configure["acceptor][listen"];
    for (const auto & it : listen) {
        std::string ip = it["ip"].asString();
        int port = it["port"].asInt();
        _listener.push_back(ListenInfo(ip, port));
    }

    return Listen();
}

void Acceptor::Run()
{
    while(_run) {
        //
        // 1. 循环等待客户端连接
        //

        //
        // 2.1 接受客户端连接
        //

        //
        // 2.2. 轮询发送客户端信息到 iohandler 进行处理
        //

        //
        // 2.3 发送客户端信息到 iohandler 并通知 iohandler
        //
    }
}

void Acceptor::Stop()
{
    _run = false;
}

bool Acceptor::Listen()
{
    for (auto & it : _listener) {
        // TODO socket param
        LogInfo("Try to listen on addr %s:%d\n", it.ip.c_str(), it.port);
        it.fd = socket(AF_INET, SOCK_STREAM, 0);
        if (it.fd < 0) {
            _errmsg = "socket() error, " + safe_strerror(errno);
            return false;
        }

        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(it.port);
        addr.sin_addr.s_addr = inet_addr(it.ip.c_str());

        if (!SetSocketOption(it.fd)) {
            return false;
        }

        if (bind(it.fd, (struct sockaddr*)&addr, sizeof(struct sockaddr)) < 0) {
            _errmsg = "bind() error, " + safe_strerror(errno);
            return false;
        }

        // TODO listen param
        if (listen(it.fd, 1000) < 0) {
            _errmsg = "listen() error, " + safe_strerror(errno);
            return false;
        } else {
            LogInfo("listen on addr %s:%d success", it.ip.c_str(), it.port);
        }
    }

    return true;
}

bool Acceptor::SetSocketOption(int fd)
{
    if (set_nonblock(fd) < 0) {
        _errmsg = "set_nonblock() error, " + safe_strerror(errno);
    }
    return true;
}

}
