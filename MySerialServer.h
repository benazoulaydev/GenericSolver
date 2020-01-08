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
    void open(int port, ClientHandler* c) override;
    void stop() override;
    int start(int port, ClientHandler* c);
};


#endif //EX4_MYSERIALSERVER_H
