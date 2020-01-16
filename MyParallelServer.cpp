//
// Created by ben on 15/01/2020.
//

#include "MyParallelServer.h"
void MyParallelServer :: open (int port, ClientHandler* c) {

    int sockfd,portno;
    struct sockaddr_in serv_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }


    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = port;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);


    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }

    this->socketServer =  sockfd;


    listen(this->socketServer,SOMAXCONN);

    start(this->socketServer, c);
}

void MyParallelServer :: stop() {
    for(vector<thread*>::iterator iterator1 = this->vectOfThread.begin(); iterator1 != this->vectOfThread.end(); iterator1++) {
        (*(iterator1))->join();
    }
    close(this->socketServer);
}

void MyParallelServer ::start(int socketID, ClientHandler *clientHandler) {
    bool is_running = true;
    int clientSock;
    bool secondConnection = false;
    while(is_running) {

        int newsockfd, clilen;

        struct sockaddr_in cli_addr;
        clilen = sizeof(cli_addr);
        if (secondConnection) {
            // set TIMEOUT option to server socket
            struct timeval timeout;
            //Initialize the timeval struct to 100 sec.
            timeout.tv_sec  = 100;
            timeout.tv_usec = 0;
            // Forcefully attaching socket to the port given
            setsockopt(socketID, SOL_SOCKET, SO_RCVTIMEO, (char*) &timeout, sizeof(struct timeval));
        }

        clientSock = accept(socketID, (struct sockaddr *)&cli_addr, (socklen_t*)&clilen);


        if(clientSock < 0) {
            if(errno == EWOULDBLOCK) {
                is_running = false;
                continue;
            }
            else {
                continue;
            }
        }
        secondConnection = true;
        vectOfThread.push_back(new thread(&openNewThread, clientSock, clientHandler));
    }
}


void MyParallelServer ::openNewThread(int clientSocket, ClientHandler *clientHandler) {
    clientHandler->handleClient(clientSocket, clientSocket);
    close(clientSocket);
}

