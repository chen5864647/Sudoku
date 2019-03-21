#ifndef _SERVER_HPP_
#define _SERVER_HPP_

#include "codec.hpp"

#include <muduo/base/Logging.h>
#include <muduo/base/Mutex.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>

#include <set>
#include <stdio.h>
#include <unistd.h>

using namespace muduo;
using namespace muduo::net;

class SudukuServer : noncopyable 
{
    public:
    SudukuServer(EventLoop* loop,
                const InetAddress& listenAddr);

    void start();

private:
    void onConnection(const TcpConnectionPtr& conn);

    void onStringMessage(const TcpConnectionPtr&,
                        const string& message,
                        Timestamp);

    typedef std::set<TcpConnectionPtr> ConnectionList;
    TcpServer server_;
    LengthHeaderCodec codec_;
    ConnectionList connections_;
};

#endif  // _SERVER_HPP_
