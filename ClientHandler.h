//
// Created by kfiry on 06/01/2020.
//

#ifndef EX4_CLIENTHANDLER_H
#define EX4_CLIENTHANDLER_H
#include <iostream>


class ClientHandler {
public:
    virtual void handleClient(int inputStream, int outputStream) = 0;
};


#endif //EX4_CLIENTHANDLER_H
