cmake_minimum_required(VERSION 3.10)
project(GenericSolver)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(GenericSolver main.cpp Server.h ClientHandler.h MySerialServer.cpp
        MySerialServer.h MyTestClientHandler.cpp MyTestClientHandler.h Solver.h
        StringReverser.h CacheManager.h State.h Searchable.h ISearcher.h Solution.h BestFirstSearch.h MatrixMaze.h
        Cell.h  SearchSolver.h BFS.h DFS.h AStar.h strinClass.h MyParallelServer.cpp MyParallelServer.h
        MyClientHandler.cpp MyClientHandler.h BestFS.h AStar2.h MatrixClientHandler.h MatrixClientHandler.cpp)