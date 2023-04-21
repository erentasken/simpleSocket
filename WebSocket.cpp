#include "WebSocket.h"

WebSocket::WebSocket() {
    server_fd = 0;
    client_fd = 0;
}

void WebSocket::close() {
    // closing the connected socket
    ::close(client_fd);
    // closing the listening socket
    shutdown(server_fd, SHUT_RDWR);
}

char* WebSocket::receiveMessage() {
    char *buffer = new char[BUFFER_SIZE];
    *buffer = { 0 };
    int valread = read(client_fd, buffer, BUFFER_SIZE);
    
    if(valread==0){
    	perror("read failed");
    	delete[] buffer;
    	return nullptr; 
    }
    
    return buffer;
}

bool WebSocket::sendMessage(char* message) {
    send(client_fd, message, strlen(message), 0);
    printf("message sent\n");
    return 1;
}

bool WebSocket::connectToServer() {
    char buffer[BUFFER_SIZE] = { 0 };
    char* hello = "Hello from client";
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return false;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

        // Convert IPv4 and IPv6 addresses from text to binary form
        if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
            printf("\nInvalid address/ Address not supported \n");
            return 0;
        }

        if (connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
            printf("\nConnection Failed \n");
            return 0;
        }
        return 1;
    }

bool WebSocket::startServer() {
    int opt = 1;
    int addrlen = sizeof(address);
    char* hello = "Hello from server";

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        return false;
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        return 0;
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        return 0;
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        return 0;
    }
    if ((client_fd = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        return 0;
    }
    return 1;
}