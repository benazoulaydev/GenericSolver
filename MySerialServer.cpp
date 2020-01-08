//
// Created by kfiry on 06/01/2020.
//
#include <thread>
#include <netinet/in.h>
#include <unistd.h>

#include "MySerialServer.h"

void MySerialServer::open(int port, ClientHandler* c) {
    std::thread thread1(&MySerialServer::start,this, port, c);
    thread1.detach();
}

int MySerialServer::start(int port, ClientHandler* c) {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello from server\n";

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port given
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt))){
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address))<0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0){
        perror("listen");
        exit(EXIT_FAILURE);
    }
    //TODO make timeout for accept!
    while(running){
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                                 (socklen_t*)&addrlen))<0){
            perror("accept error");
            exit(EXIT_FAILURE);
        }
        c->handleClient(new_socket, new_socket);
    }

    //close the socketFD
    close(server_fd);
    return 0;
}

void MySerialServer::stop() {
    running = false;
}
