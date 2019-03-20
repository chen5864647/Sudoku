#include "server.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;

Server::Server() : domain(AF_INET), type(SOCK_STREAM) { 
    bzero(&this->addr4, sizeof(addr4));
    bzero(&this->addr6, sizeof(addr6));
}

Server::Server(int doamin, int type) : domain(doamin), type(type) {
    bzero(&this->addr4, sizeof(addr4));
    bzero(&this->addr6, sizeof(addr6));
}

Server::~Server() {
    try {
        close(sockfd);
    } catch (exception ex) {
        cerr << ex.what() << endl;
    }
}

bool Server::Socket(int domain, int type, int protocol) {
    this->sockfd = socket(domain, type, 0);
    if (this->sockfd < 0) {
        throw range_error("error info!");
        return false;
    }
    else 
        return true;
}

void Server::setAddr(const struct sockaddr_in &addr) {
    // IPv4

    domain = addr.sin_family;

    if (domain == AF_INET) {
        addr4.sin_family            = AF_INET;
        addr4.sin_port              = addr.sin_port;
        addr4.sin_addr.s_addr       = addr.sin_addr.s_addr;
    }
    // else if (domain == AF_INET6) {
    //     addr6.sin6_family = AF_INET;
    //     addr6.sin6_port = addr.sin_port;
    //     addr6.sin6_addr.__in6_u = addr.sin_addr.s_addr;
    // }
}

bool Server::Bind() {
    // IPv4
    if (domain == AF_INET) {
        if (bind(sockfd, (SA *)&addr4, sizeof(addr4)) < 0)
            return false;
        else return true;
    }
    // only IPv4
    else 
        return false;
}

bool Server::Listen(int backlog) {
    if (listen(this->sockfd, backlog) < 0)
        return false;
    else return true;
}

void Server::loop() {
    while (true);
}

bool Server::Accept() {
    try {
        this->connfd = accept(sockfd, (SA*)nullptr, nullptr);
    } catch (exception ex) {
        cerr << ex.what() << endl;
        return false;
    }

    return true;
}
