//
// Created by kfiry on 06/01/2020.
//

#ifndef EX4_SERVER_H
#define EX4_SERVER_H


#include "ClientHandler.h"

class Server {
public:
    /**
     * open the server
     * @param port
     * @param c
     */
    virtual void open(int port, ClientHandler* c) = 0;
    /**
     * stop the server
     */
    virtual void stop() = 0;
    virtual ~Server(){}

};


#endif //EX4_SERVER_H
