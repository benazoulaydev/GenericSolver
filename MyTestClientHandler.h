//
// Created by kfiry on 06/01/2020.
//

#ifndef EX4_MYTESTCLIENTHANDLER_H
#define EX4_MYTESTCLIENTHANDLER_H


#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"

class MyTestClientHandler : public ClientHandler{
private:
    Solver<std::string,std::string>* solver;
    CacheManager<std::string>* cm;
public:
    MyTestClientHandler(Solver<std::string, std::string> *pSolver){
        solver = pSolver;
    }

    void handleClient(int inputStream, int outputStream) override;

};


#endif //EX4_MYTESTCLIENTHANDLER_H
