#ifndef WEBSOCKET_H
#define WEBSOCKET_H

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

class WebSocket {
public:
    WebSocket();
    bool startServer();
    bool connectToServer();
    bool sendMessage(char* message);
    char* receiveMessage();
    void closeConnection();
    void close();

private:
    int server_fd, client_fd;
    struct sockaddr_in address, serv_addr;
};

#endif // WEBSOCKET_H
