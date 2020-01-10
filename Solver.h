//
// Created by kfiry on 06/01/2020.
//

#ifndef EX4_SOLVER_H
#define EX4_SOLVER_H

template <typename Problem, typename Sol>
class Solver{
public:
    virtual Sol solve(Problem p) = 0;
};


#endif //EX4_SOLVER_H
