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

class SearchSolver : public Solver<Searchable<Cell>, string>{
private:
    ISearcher<Cell>* searcher;
    int idAlgo;
public:
    SearchSolver(ISearcher<Cell>* s){
        idAlgo = s->getIdAlgo();
        searcher = s;
    }
    SearchSolver* clone(){
        return new SearchSolver(searcher->clone());
    }

    /**
     * search given a searchable for the solution
     * @param s
     * @return the solution
     */
    string solve(Searchable<Cell>* p) override {
        Solution<Cell> *s = searcher->search(p);
        cout<<searcher->getNumberOfNodeEvaluated()<<endl;
        string sol = "";
        auto &path = *s->getPath();
        int size = path.size();
        int cost = p->cost(path[0]);
        for(int i = 0; i<size-1 ; ++i){
            sol+=p->direction(path[i],path[i+1]);
            cost += p->cost(path[i+1]);
            sol += " ("+to_string(cost)+")";
            if(i != size-2){
                sol+=" ,";
            }
        }
        return sol;
    }
    /**
     * id of algo for hash name
     * @return
     */
    int getIdAlgo() {
        return idAlgo;
    }


    ~SearchSolver(){}

};


#endif //GENERICSOLVER_SEARCHSOLVER_H
