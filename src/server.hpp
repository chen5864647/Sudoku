#ifndef _SERVER_HPP_
#define _SERVER_HPP_

#include "unp.hpp"
#include <utility>
#include <string>
#include "sudoku.hpp"

class Server {

public:
    Server();
    Server(int domain, int type);
    ~Server();

    void setAddr(const struct sockaddr_in &addr);

    bool Socket(int domain, int type, int protocol);

    bool Bind();
    
    bool Listen(int backlog = LISTENQ);

    void loop();

    bool Accept();

    ssize_t Send(int sockfd, const char *buf, size_t len, int flags = 0);

    int Recv(int sockfd, char *buf, int len, int flags = 0);  

    int Close(int fd);

private:

    int domain;
    int type;

    int sockfd;
    int connfd;

    sockaddr_in     addr4;  // Ipv4
    sockaddr_in6    addr6;  // Ipv6

    char buffer[MAXLINE];
};

#endif  // _SERVER_HPP_