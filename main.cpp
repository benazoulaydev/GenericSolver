#include <iostream>
#include <chrono>
#include <thread>
#include "MySerialServer.h"
#include "MyParallelServer.h"
#include "MyTestClientHandler.h"
#include "StringReverser.h"
#include "MatrixMaze.h"
#include "Solution.h"
#include "ISearcher.h"
#include "BestFirstSearch.h"
#include "SearchSolver.h"
#include "BFS.h"
#include "DFS.h"
#include "AStar.h"
#include <queue>
using namespace std;

int main() {
//    Solution<Cell> s = SearchSolver(new BestFirstSearch<Cell>()).solve(new MatrixMaze());
////    Solution<Cell> s = SearchSolver(new DFS<Cell>()).solve(new MatrixMaze());
//    for(const auto p : *s.getPath()){
//        cout<<"("<<p.getI()<<","<<p.getJ()<<")";
//    }
//    Solution<Cell> s2 = SearchSolver(new AStar<Cell>()).solve(new MatrixMaze());
//    for(const auto p : *s2.getPath()){
//        cout<<"("<<p.getI()<<","<<p.getJ()<<")";
//    }
//    cout<<endl;



//    BFS<Cell> bfs{};
//    auto m = new MatrixMaze();
//    cout<<bfs.absDistance(new MatrixMaze(), *m->getInitState())<<endl;



    StringReverser sr{};
    //MyParallelServer mss{};
//    MyTestClientHandler ch{&sr};
//    mss.open(5600, &ch);
    ClientHandler *testClientHandler = new MyTestClientHandler(&sr);
    MyParallelServer server;
    server.open(5611, testClientHandler);
    server.stop();
    delete(testClientHandler);
    //std::this_thread::sleep_for(std::chrono::milliseconds(200000));

    return 0;
}


