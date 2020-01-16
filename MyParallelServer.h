//
// Created by ben on 15/01/2020.
//

#ifndef GENERICSOLVER_MYPARALLELSERVER_H
#define GENERICSOLVER_MYPARALLELSERVER_H

#include "Server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <thread>
#include <unistd.h>
#include <condition_variable>
#include <chrono>
#include <vector>
using namespace std;
class MyParallelServer : public Server {
private:
    vector<thread*> vectOfThread;
    int socketServer;
public :
    void open(int port, ClientHandler* c);
    void stop();
    void start(int socketID, ClientHandler* clientHandler);
    static void openNewThread(int clientSocket, ClientHandler* clientHandler);
    ~MyParallelServer() {
        for(int i = 0; i < vectOfThread.size(); i++) {
            delete(vectOfThread.at(i));
        }
    }
};

#endif //GENERICSOLVER_MYPARALLELSERVER_H
