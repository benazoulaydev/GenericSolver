//
// Created by kfiry on 06/01/2020.
//

#ifndef EX4_MYSERIALSERVER_H
#define EX4_MYSERIALSERVER_H


#include "Server.h"

class MySerialServer: public Server {
private:
    bool running = true;
public:
    /**
     * open the serial server
     * @param port
     * @param c
     */
    void open(int port, ClientHandler* c) override;
    /**
     * stop the serial server
     */
    void stop() override;
    /**
     * start the serial server
     * @param socketID
     * @param clientHandler
     */
    int start(int port, ClientHandler* c);

    ~MySerialServer(){}

};


#endif //EX4_MYSERIALSERVER_H
