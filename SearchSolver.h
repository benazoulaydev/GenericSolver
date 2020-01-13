//
// Created by kfiry on 13/01/2020.
//

#ifndef GENERICSOLVER_SEARCHSOLVER_H
#define GENERICSOLVER_SEARCHSOLVER_H


#include "Solver.h"
#include "Cell.h"
#include "Searchable.h"
#include "Solution.h"
#include "ISearcher.h"

class SearchSolver : public Solver<Searchable<Cell>, Solution<Cell>>{
private:
    ISearcher<Cell>* searcher;
public:
    SearchSolver(ISearcher<Cell>* s){
        searcher = s;
    }
    Solution<Cell> solve(Searchable<Cell>* p) override {
        return *searcher->Search(p);
    }
};


#endif //GENERICSOLVER_SEARCHSOLVER_H
