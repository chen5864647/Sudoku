#include "server.hpp"

int main(int argc, char **argv) {

    LOG_INFO << "pid = " << getpid();
    if (argc > 1) {
        EventLoop loop;
        uint16_t port = static_cast<uint16_t>(atoi(argv[1]));
        InetAddress serverAddr(port);
        SudukuServer server(&loop, serverAddr);
        server.start();
        loop.loop();
    }
    else
        printf("Usage: %s port\n", argv[0]);

    return 0;
}