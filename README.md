# GENERIC SOLVER C++
Link to [our](https://github.com/benazoulaydev/GenericSolver) project's repository.
## Description
The purpose of the code is to open a connection with clients using socket, with serial server or parallel server (multi-thread) clients can send problem to the server. And the server solve their problems using algorithms.
Solving the problem is doing by using a Searcher class that implements an individual algorithm.
Here we develop searchable Algo such as DFS, BFS, A*, BestFs to find the solution of a given problem. The possibilities are endless, this is a strong base to begin with to problem solving programs.

After testing all the algorithms we discover that the Best First Search won the others. A* is an algorithm that learn from itself and do not always find the solution, BFS and Dfs are not algoritm that find the shortest path with weighted edges. As a result in our main function we are running a parallel server that use the Best First Search algorithm to solve the given problems. The problems given from the client for now are graphs, represented as matrix but can easily be transfer to any other representation by implement new Searchable class and a relevent Searcher class.



## Installation
You can choose Port as desired.
#### 1- Complie the program code:

```bash
g++ -std=c++14 
*.cpp -Wall -Wextra -Wshadow 
-Wnon-virtual-dtor -pedantic -o a.out -pthread
```

#### 2- Run a.out with an input port, the server will be listening on (as you wish if no input port default : 5600)

```bash
./a.out port
```

#### 3- The program is now waitint for client's connections, wait to receive problems and return back solution.

## Additional info
you can  find the file "Experiment-results.pdf" in the repository with statistic about all the fourth algorithms that been run on 10 different matrix in different sizes between 10-50.