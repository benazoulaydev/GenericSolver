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
#include "BestFirstSearch.h"
#include "BestFS.h"
#include "SearchSolver.h"
#include "BFS.h"
#include "DFS.h"
#include "AStar.h"
#include "AStar2.h"
#include <queue>
#include <algorithm>
#include <chrono>
using namespace std;
using namespace std::chrono;
int main() {
//    vector<int> m;
//    m.push_back(1);m.push_back(2);m.push_back(3);
//    m.push_back(1);m.push_back(2);m.push_back(3);
//    m.push_back(1);m.push_back(2);m.push_back(1);
//    BestFS<Cell> b{};
//    Cell c1(0,0);
//    Cell c2(2,2);
//    MatrixMaze matrixMaze(c1,c2,&m,3);
//    string dd = SearchSolver(&b).solve(&matrixMaze);
//    cout<<dd<<endl;
//
    StringReverser sr{};
    //MyParallelServer mss{};
//    MyTestClientHandler ch{&sr};
//    mss.open(5600, &ch);
    ClientHandler *testClientHandler = new MatrixClientHandler(&sr);
    MyParallelServer server;
    server.open(5611, testClientHandler);
    server.stop();
    delete(testClientHandler);
//    //std::this_thread::sleep_for(std::chrono::milliseconds(200000));

    return 0;
}