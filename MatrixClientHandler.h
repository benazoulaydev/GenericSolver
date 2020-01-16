//
// Created by kfiry on 16/01/2020.
//

#ifndef GENERICSOLVER_MATRIXCLIENTHANDLER_H
#define GENERICSOLVER_MATRIXCLIENTHANDLER_H
#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"


class MatrixClientHandler  : public ClientHandler{
private:
    Solver<std::string,std::string>* solver;
    CacheManager<std::string>* cm;
public:
    MatrixClientHandler(Solver<std::string, std::string> *pSolver){
        solver = pSolver;
    }

    void handleClient(int socketFD, int outputStream) override{

    }

};


#endif //GENERICSOLVER_MATRIXCLIENTHANDLER_H
