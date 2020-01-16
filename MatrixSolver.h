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
public:
    string solve(MatrixMaze *p) override{
        Solution<Cell> s = SearchSolver(new DFS<Cell>()).solve(new MatrixMaze());
    }
};


#endif //GENERICSOLVER_MATRIXSOLVER_H
