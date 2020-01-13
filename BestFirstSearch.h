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
    multiset<State<T>>* openList;
    unordered_map<T, State<T>>* openListMap;
    unordered_map<T, State<T>>* closed;
    int evaluatedNodes;
    Solution<T> *backTrace(const State<T>* goalState, State<T> *init);
public:
    BestFirstSearch(){
        openList = new multiset<State<T>>();
        openListMap = new unordered_map<T, State<T>>();
        evaluatedNodes=0;
    }
    void addToOpenList(State<T>* state){
        openList->insert(*state);
        openListMap->emplace(state->getState(), *state);
    }
    bool openContains(T state){
        return openListMap->find(state) != openListMap->end();
    }
    double costToState(T state){
        return (openListMap->at(state)).getCost();
    }
    int openListSize(){
        return openList->size();
    }
    int getNumberOfNodeEvaluated() override {
        return evaluatedNodes;
    }
    void updateState(T state, T newCameFrom, double newCost){
        State<T> updatedState = openListMap->at(state);
        updatedState.setCameFrom(newCameFrom);
        updatedState.setCost(newCost);
    }
    const State<T>* popOpenList(){
        evaluatedNodes++;
        typename set<State<T>>::iterator top = openList->begin();
        openList->erase(top);
        openListMap->erase(top->getState());
        return &*top;
    }
    Solution<T>* Search(Searchable<T>* searchable) override;
};

template<typename T>
Solution<T> *BestFirstSearch<T>::Search(Searchable<T>* searchable) {
    addToOpenList(searchable->getInitState());
    closed = new unordered_map<T, State<T>>();
    while(openListSize() > 0){
        const State<T>* n = this->popOpenList();
        closed->emplace(n->getState(), *n);
        if(searchable->isGoalState(n)){
            return backTrace(n,searchable->getInitState()); // find the best path from the openList;
        }
        auto succerssors = searchable->getAllPossibleStates(n);
        for(State<T>* s : *succerssors){
            s->setCost(s->getCost()+n->getCost());
            if(closed->find(s->getState()) == closed->end()){
                if(!openContains(s->getState())){
                    addToOpenList(s);
                } else {
                    double newCost = s->getCost();
                    if(newCost < costToState(s->getState())){
                        updateState(s->getState(), n->getState(), newCost);
                    }
                }
            }
        }
    }
    cout<<"bestFS did not work "<<getNumberOfNodeEvaluated()<<endl;
}

template<typename T>
Solution<T> *BestFirstSearch<T>::backTrace(const State<T> *goalState, State<T> *init) {
    Solution<T>* solution = new Solution<T>();
    const State<T>* tempState;
    tempState = goalState;
    while(tempState->getState() != init->getState()){
        solution->addStateFront(tempState->getState());
        tempState = &closed->at(tempState->getCameFrom());
    }
    solution->addStateFront(tempState->getState());
    return solution;
}
#endif //GENERICSOLVER_BESTFIRSTSEARCH_H
