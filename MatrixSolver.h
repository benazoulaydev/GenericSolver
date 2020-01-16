//
// Created by kfiry on 16/01/2020.
//

#ifndef GENERICSOLVER_MATRIXSOLVER_H
#define GENERICSOLVER_MATRIXSOLVER_H


#include "MatrixMaze.h"
#include "Solution.h"
#include "Cell.h"

class MatrixSolver : public Solver<MatrixMaze, Solution < Cell>>{
public:
    Solution solve(MatrixMaze *p) override;
};


#endif //GENERICSOLVER_MATRIXSOLVER_H
