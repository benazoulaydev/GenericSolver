//
// Created by kfiry on 09/01/2020.
//

#ifndef GENERICSOLVER_BESTFIRSTSEARCH_H
#define GENERICSOLVER_BESTFIRSTSEARCH_H

#include "Searcher.h"
#include "Solution.h"
#include <bits/stdc++.h>

template <typename T>
class BestFirstSearch : public Searcher<T>{
private:
    map<T, State<T>*>* closed;
    Solution<T> *backTrace(State<T>* goalState);
public:
    Solution<T>* Search(Searchable<T>* searchable) override;
};

template<typename T>
Solution<T> *BestFirstSearch<T>::Search(Searchable<T>* searchable) {
    Searcher<T>::addToOpenList(searchable->getInitState());
    closed = new map<T, State<T>*>();
    while(Searcher<T>::openListSize() > 0){
        State<T>* n = this->popOpenList();
        closed->emplace(n->getState(), n);
        if(searchable->isGoalState(n)){
            return backTrace(n); // find the best path from the openList;
        }
        auto succerssors = searchable->getAllPossibleStates(n);
        for(State<T>* s : *succerssors){
            if(closed->find(s->getState()) == closed->end() && !Searcher<T>::openContains(s->getState())){
                Searcher<T>::addToOpenList(s);
            } else {
                if(Searcher<T>::openContains(s->getState())){
                    double newCost = s->getCost() + n->getCost();
                    if(newCost < Searcher<T>::costToState(s->getState())){
                        Searcher<T>::updateState(s->getState(), n->getState(), newCost);
                    }
                }
            }
        }
    }
    cout<<"bestFS did not work"<<endl;
}

template<typename T>
Solution<T> *BestFirstSearch<T>::backTrace(State<T>*goalState) {
    Solution<T>* solution = new Solution<T>();
    State<T>* tempState;
    tempState = goalState;
    while(tempState != nullptr){
        solution->addStateFront(tempState->getState());
        tempState = closed->at(tempState->getCameFrom());
    }
    return solution;
}

#endif //GENERICSOLVER_BESTFIRSTSEARCH_H
