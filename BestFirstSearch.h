//
// Created by kfiry on 09/01/2020.
//

#ifndef GENERICSOLVER_BESTFIRSTSEARCH_H
#define GENERICSOLVER_BESTFIRSTSEARCH_H

#include "ISearcher.h"
#include "Solution.h"
#include <bits/stdc++.h>


template <typename T>
class BestFirstSearch : public ISearcher<T>{
private:
    unordered_map<T, State<T>&> openSet;
    unordered_map<T, State<T>&> closed;
    int evaluatedNodes = 0;
    Solution<T> *backTrace(State<T>* goalState, State<T> *init);
    Searchable<T>* searchableI;
public:
    void addToOpenList(State<T>* state){
        openSet.emplace(state->getState(), *state);
    }
    bool openContains(T state){
        return openSet.find(state) != openSet.end();
    }
    int getNumberOfNodeEvaluated() override {
        return evaluatedNodes;
    }
    State<T>* popOpenList(){
        evaluatedNodes++;
        State<T>* current = &openSet.begin()->second;
        for(auto pair: openSet){
            if(pair.second.getCost() < current->getCost()) {
                current = &pair.second;
            }
        }
        openSet.erase(current->getState());
        return current;
    }
    Solution<T>* search(Searchable<T>* searchable) override;
};


template<typename T>
Solution<T> *BestFirstSearch<T>::search(Searchable<T>* searchable) {
    searchableI = searchable;
    addToOpenList(searchable->getInitState());
    while(!openSet.empty()){
        State<T>* n = this->popOpenList();
        closed.emplace(n->getState(), *n);
        if(searchable->isGoalState(n)){
            return backTrace(n,searchable->getInitState()); // find the best path from the openList;
        }
        auto succerssors = searchable->getAllPossibleStates(n);
        for(State<T>* s : *succerssors){
            s->setCost(s->getCost()+n->getCost());
            if(closed.find(s->getState()) == closed.end() && !openContains(s->getState())){
                addToOpenList(s);
            } else {
            }
        }
    }
    cout<<"bestFS did not work "<<getNumberOfNodeEvaluated()<<endl;
}


template<typename T>
Solution<T> *BestFirstSearch<T>::backTrace(State<T> *goalState, State<T> *init) {
    Solution<T>* solution = new Solution<T>();
    State<T>* tempState;
    tempState = goalState;
    double totalCost = 0;
    while(tempState->getState() != init->getState()){
        totalCost+=searchableI->cost(tempState->getState());
        solution->addStateFront(tempState->getState());
        tempState = &closed.at(tempState->getCameFrom());
    }
    return solution;
}
#endif //GENERICSOLVER_BESTFIRSTSEARCH_H
