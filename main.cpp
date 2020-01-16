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
#include "BestFS2.h"
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
//    // Get starting timepoint
//    auto start = high_resolution_clock::now();
//
//    // Call the function, here sort()
//    Solution<Cell> s = SearchSolver(new BestFS<Cell>()).solve(new MatrixMaze());
//
//    // Get ending timepoint
//    auto stop = high_resolution_clock::now();
//
//    // Get duration. Substart timepoints to
//    // get durarion. To cast it to proper unit
//    // use duration cast method
//    auto duration = duration_cast<microseconds>(stop - start);
//
//    cout << "Time taken by function: "
//         << duration.count() << " microseconds" << endl;
//
//    // Get starting timepoint
//     start = high_resolution_clock::now();
//
//    // Call the function, here sort()
//    Solution<Cell> s2 = SearchSolver(new BestFirstSearch<Cell>()).solve(new MatrixMaze());
//
//    // Get ending timepoint
//     stop = high_resolution_clock::now();
//
//    // Get duration. Substart timepoints to
//    // get durarion. To cast it to proper unit
//    // use duration cast method
//     duration = duration_cast<microseconds>(stop - start);
//
//    cout << "Time taken by function: "
//         << duration.count() << " microseconds" << endl;
//
//    // Call the function, here sort()
//    Solution<Cell> s21 = SearchSolver(new BestFS2<Cell>()).solve(new MatrixMaze());
//
//    // Get ending timepoint
//    stop = high_resolution_clock::now();
//
//    // Get duration. Substart timepoints to
//    // get durarion. To cast it to proper unit
//    // use duration cast method
//    duration = duration_cast<microseconds>(stop - start);
//
//    cout << "Time taken by BestFS2: "
//         << duration.count() << " microseconds" << endl;
//    // Get starting timepoint
//     start = high_resolution_clock::now();
//
//    // Call the function, here sort()
//    Solution<Cell> s3 = SearchSolver(new AStar<Cell>()).solve(new MatrixMaze());
//
//    // Get ending timepoint
//     stop = high_resolution_clock::now();
//
//    // Get duration. Substart timepoints to
//    // get durarion. To cast it to proper unit
//    // use duration cast method
//     duration = duration_cast<microseconds>(stop - start);
//
//    cout << "Time taken by function: "
//         << duration.count() << " microseconds" << endl;
//
//    // Get starting timepoint
//    start = high_resolution_clock::now();
//
//    // Call the function, here sort()
//    Solution<Cell> s4 = SearchSolver(new AStar2<Cell>()).solve(new MatrixMaze());
//
//    // Get ending timepoint
//    stop = high_resolution_clock::now();
//
//    // Get duration. Substart timepoints to
//    // get durarion. To cast it to proper unit
//    // use duration cast method
//    duration = duration_cast<microseconds>(stop - start);
//
//    cout << "Time taken by function: "
//         << duration.count() << " microseconds" << endl;

//    vector<int> m;
//    m.push_back(1);m.push_back(2);m.push_back(3);
//    m.push_back(1);m.push_back(2);m.push_back(3);
//    m.push_back(1);m.push_back(2);m.push_back(1);
//    string dd = SearchSolver(new BestFirstSearch<Cell>()).solve(new MatrixMaze(*new Cell(0,0),*new Cell(2,2), &m, 3));
//    cout<<dd<<endl;
//    Solution<Cell> s = SearchSolver(new BestFS<Cell>()).solve(new MatrixMaze());
//    Solution<Cell> s = SearchSolver(new DFS<Cell>()).solve(new MatrixMaze());
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


//
//    StringReverser sr{};
//    //MyParallelServer mss{};
////    MyTestClientHandler ch{&sr};
////    mss.open(5600, &ch);
//    ClientHandler *testClientHandler = new MyTestClientHandler(&sr);
//    MyParallelServer server;
//    server.open(5611, testClientHandler);
//    server.stop();
//    delete(testClientHandler);
//    //std::this_thread::sleep_for(std::chrono::milliseconds(200000));


    StringReverser sr{};
    //MyParallelServer mss{};
//    MyTestClientHandler ch{&sr};
//    mss.open(5600, &ch);
    ClientHandler *testClientHandler = new MatrixClientHandler(&sr);
    MyParallelServer server;
    server.open(5611, testClientHandler);
    server.stop();
    delete(testClientHandler);
    //std::this_thread::sleep_for(std::chrono::milliseconds(200000));

    return 0;
}