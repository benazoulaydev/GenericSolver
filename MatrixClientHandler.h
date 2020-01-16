//
// Created by ben on 16/01/2020.
//

#ifndef GENERICSOLVER_MATRIXCLIENTHANDLER_H
#define GENERICSOLVER_MATRIXCLIENTHANDLER_H

#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"
#include <strings.h>
#include <unistd.h>
#include <sys/socket.h>
#include <cstring>
#include <algorithm>
#include "MyTestClientHandler.h"
#include "Searchable.h"
#include <vector>
#include <sstream>
#include "Cell.h"
#include "MatrixMaze.h"
#include "BestFirstSearch.h"
#include "SearchSolver.h"


class MatrixClientHandler : public ClientHandler{
private:
    Solver<std::string,std::string>* solver;
    CacheManager<std::string>* cm;
public:
    MatrixClientHandler(Solver<std::string, std::string> *pSolver){
        solver = pSolver;
    }
    void handleClient(int socketFD, int outputStream) override;
    vector<int> split(string line, char c);

};


#endif //GENERICSOLVER_MATRIXCLIENTHANDLER_H
