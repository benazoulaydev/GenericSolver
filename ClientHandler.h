//
// Created by kfiry on 06/01/2020.
//

#ifndef EX4_CLIENTHANDLER_H
#define EX4_CLIENTHANDLER_H
#include <iostream>


class ClientHandler {
public:
    //TODO 1 param only
    /**
     * handle the client with given socket
     * @param inputStream
     * @param outputStream
     */
    virtual void handleClient(int inputStream, int outputStream) = 0;
    virtual ~ClientHandler() {

    }
};


#endif //EX4_CLIENTHANDLER_H
