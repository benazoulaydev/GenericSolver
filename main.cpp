#include <iostream>
#include <chrono>
#include <thread>
#include "MySerialServer.h"
#include "MyParallelServer.h"
#include "MyTestClientHandler.h"
#include "MatrixClientHandler.h"
#include "MatrixMaze.h"
#include "StringReverser.h"
#include "Solution.h"
#include "ISearcher.h"
#include "BestFS.h"
#include "SearchSolver.h"
#include "BFS.h"
#include "DFS.h"
#include "AStar_v1.h"
#include "AStar.h"
#include <queue>
#include <algorithm>
#include <chrono>
using namespace std;
using namespace std::chrono;
int main(int argc, char* argv[]) {
    char* port;
    string defPort = "5600";
    if (argc < 2) {
        port = const_cast<char *>(defPort.c_str());
    } else {
        port =argv[1];
    }

    ISearcher<Cell>* s = new BestFS<Cell>();
    SearchSolver* srchSlv_t_y = new SearchSolver(s);
    ClientHandler *testClientHandler = new MatrixClientHandler(s, srchSlv_t_y);
    MyParallelServer server;
    server.open(atoi(port), testClientHandler);
    server.stop();
    delete(testClientHandler);

    return 0;
}