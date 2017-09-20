#ifndef RALPH_SERVER_ACCEPTOR_H
#define RALPH_SERVER_ACCEPTOR_H

#include <memory>
#include <string>

#include <json/value.h>

#include "ralph/common/poller.h"

namespace ralph
{

struct ListenInfo {
    explicit ListenInfo(const std::string & listen_ip,
                      int listen_port)
        : ip(listen_ip)
        , port(listen_port) {}

    std::string ip;
    int port;
    int fd;
};

class Acceptor {
public:
    Acceptor(const Json::Value & configure);
    virtual ~Acceptor();
    bool Initialize();
    void Run();
    void Stop();

private:
    bool Listen();
    bool SetSocketOption(int fd);

private:
    bool _run;
    const Json::Value & _configure;
    int _last_handler;
    std::unique_ptr<Poller> _poller;
    std::vector<ListenInfo> _listener;

    std::string _errmsg;
};

} /* namespace ralph */


#endif // RALPH_SERVER_ACCEPTOR_H
