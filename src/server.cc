#include "server.hpp"
#include "codec.hpp"
#include "sudoku.hpp"
#include <array>
#include <string>
#include <utility>

using namespace muduo;
using namespace muduo::net;
using namespace std;

SudukuServer::SudukuServer(EventLoop* loop,
                const InetAddress& listenAddr)
: server_(loop, listenAddr, "ChatServer"),
codec_(std::bind(&SudukuServer::onStringMessage, this, _1, _2, _3)) {
    server_.setConnectionCallback(
        std::bind(&SudukuServer::onConnection, this, _1)
    );

    server_.setMessageCallback(
        std::bind(&LengthHeaderCodec::onMessage, &codec_, _1, _2, _3)
    );
}

void SudukuServer::start() {
    server_.start();
}

void SudukuServer::onConnection(const TcpConnectionPtr& conn) {

    LOG_INFO << conn->localAddress().toIpPort() << " -> "
             << conn->peerAddress().toIpPort() << " is "
             << (conn->connected() ? "UP" : "DOWN");

    if (conn->connected())
        connections_.insert(conn);
    else
        connections_.erase(conn);
}

void SudukuServer::onStringMessage(const TcpConnectionPtr&,
                        const string& message,
                        Timestamp) {
/*  
    for (ConnectionList::iterator it = connections_.begin();
        it != connections_.end();
        ++it)
        codec_.send(get_pointer(*it), message);
*/
    // logic

    string tsp(message);
    size_t len = tsp.size();

    array<array<unsigned short, 9>, 9> temp;
    array<unsigned short, 9> ttemp;
    unsigned short value, i, j;

    string error("This is a error chess!");
    if (len != 81) {
        for (ConnectionList::iterator it = connections_.begin();
            it != connections_.end();
            ++it)
            codec_.send(get_pointer(*it), error);
    }
    else {
        for (i = 0; i < 9; ++i) {
            for (j = 0; j < 9; ++j) {
                // array<unsigned short, 9> ttemp;
                ttemp[j] = static_cast<unsigned short>(tsp[i*9 + j] - '0');
            }
            temp[i] = ttemp;
        }
        Sudoku sudoku(temp);
        bool result = sudoku.reaction();
        if (result) {
            string win("There is a goog answer");
            for (ConnectionList::iterator it = connections_.begin();
            it != connections_.end();
            ++it)
            codec_.send(get_pointer(*it), win);
        }
        else {
            string fail("There is no answer");
            for (ConnectionList::iterator it = connections_.begin();
            it != connections_.end();
            ++it)
            codec_.send(get_pointer(*it), fail);
        }
    }
    // Sudoku sudoku();

}
