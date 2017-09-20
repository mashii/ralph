#ifndef RALPH_SERVER_HANDLER_BASE_H
#define RALPH_SERVER_HANDLER_BASE_H


namespace ralph
{

struct Header {
    int magic;
    int length;
    char payload[0];
};

class HandlerBase
{
public:
    virtual int GetMsgLength(const char * buf, int len) const;
    virtual int OnMessage(const char * input, int il) const;
    virtual int Router(const char * buf, int len) const;

protected:
    int SendToIoHandler(const char * output, int len);

}; // class HandlerBase

} /* namespace ralph */


#endif // RALPH_SERVER_HANDLER_BASE_H
