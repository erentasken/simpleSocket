#include<iostream>
#include<thread>
#include "WebSocket.h"
#include<unistd.h>

WebSocket server;
void receive_thread(){
    char* received_message;
    while(true) {
        received_message = server.receiveMessage();
        std::cout << "Received message: " << received_message << std::endl;	
        sleep(1);        
    }
    delete[] received_message;
}

void send_thread(){
    while(true){
        server.sendMessage("Hello from server");
        sleep(1);
    }
}

void server_test() {
    bool flag = server.startServer();
    if (!flag) {
        std::cout << "Server start failed" << std::endl;
        pthread_exit(NULL);
    }
    std::cout << "Server started" << std::endl;
    

    
    
    std::thread receiveThread(receive_thread);
    receiveThread.detach();
    std::thread sendThread(send_thread);
    sendThread.detach();

    sleep(10); // life-time of websocket server
    server.close();
}

int main() {
	server_test();
    return 0;
}

