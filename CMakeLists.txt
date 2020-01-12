cmake_minimum_required(VERSION 3.10)
project(GenericSolver)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(GenericSolver main.cpp Server.cpp Server.h ClientHandler.cpp ClientHandler.h MySerialServer.cpp MySerialServer.h MyTestClientHandler.cpp MyTestClientHandler.h Solver.cpp Solver.h StringReverser.cpp StringReverser.h CacheManager.h State.h Searchable.h SearcherInterface.h Searcher.h Solution.h BestFirstSearch.h MatrixMaze.h Cell.h strinClass.h)