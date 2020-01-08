//
// Created by kfiry on 06/01/2020.
//

#ifndef EX4_SERVER_H
#define EX4_SERVER_H


#include "ClientHandler.h"

class Server {
public:
    virtual void open(int port, ClientHandler* c) = 0;
    virtual void stop() = 0;
};


#endif //EX4_SERVER_H
