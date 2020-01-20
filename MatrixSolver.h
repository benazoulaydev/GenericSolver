//
// Created by kfiry on 16/01/2020.
//

#ifndef GENERICSOLVER_MATRIXSOLVER_H
#define GENERICSOLVER_MATRIXSOLVER_H


#include "MatrixMaze.h"
#include "Solution.h"
#include "Cell.h"
#include "Solver.h"

using namespace std;

class MatrixSolver : public Solver<MatrixMaze, string>{
private:
    /*
     * idSolver = 1 if Astar
     * idSolver = 2 if Astar2
     * idSolver = 3 if BestFirstSearch
     * idSolver = 4 if BestFS
     * idSolver = 5 if BestFs2
     * idSolver = 6 if BFS
     * idSolver = 7 if DFS
     *
     */
    int idSolver = 0;
public:
    string solve(MatrixMaze *p) override{
        Solution<Cell> s = SearchSolver(new DFS<Cell>()).solve(new MatrixMaze());
        idSolver = 7;
    }
    int getIdSolver() {
        return  idSolver;
    }
};


#endif //GENERICSOLVER_MATRIXSOLVER_H
