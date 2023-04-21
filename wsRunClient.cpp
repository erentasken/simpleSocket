#include<iostream>
#include "WebSocket.h"
#include<thread>
#include<unistd.h>

WebSocket client;

void send_thread(){
    while(1){
        client.sendMessage("Hello from client");
        sleep(2);
    }
}

void receive_thread(){
    

    char* received_message;
    while(true) {
        received_message = client.receiveMessage();
        std::cout << "Received message: " << received_message << std::endl;
        sleep(1);
    }
    delete[] received_message;
    
}

void client_test() {
    
    bool flag = client.connectToServer();
    if (!flag) {
        std::cout << "Connection failed" << std::endl;
        pthread_exit(NULL);
    }
    std::cout << "Connection established" << std::endl;
    

    

    std::thread receiveThread(receive_thread);
    receiveThread.detach();
    std::thread sendThread(send_thread);
    sendThread.detach();
    
    sleep(10); // life-time of websocket client
    client.close();
}

int main() {
	client_test();
	
    return 0;
}

