//
// Created by kfiry on 09/01/2020.
//

#ifndef GENERICSOLVER_SEARCHER_H
#define GENERICSOLVER_SEARCHER_H

#include "SearcherInterface.h"
#include <queue>
#include <unordered_map>
#include <set>

using namespace std;

template <typename T>
class Searcher : public SearcherInterface<T>{
private:
    set<State<T>*>* openList;
    unordered_map<T, State<T>*>* openListMap;
    int evaluatedNodes;
public:
    Searcher(){
        openList = new set<State<T>*>();
        openListMap = new unordered_map<T, State<T>*>();
        evaluatedNodes=0;
    }
    void addToOpenList(State<T>* state){
        openList->insert(state);
        openListMap->emplace(state->getState(), state);
    }
    bool openContains(T state){
        return openListMap->find(state) != openListMap->end();
    }
    double costToState(T state){
        return (openListMap->at(state))->getCost();
    }
    int openListSize(){
        return openList->size();
    }
    int getNumberOfNodeEvaluated(){
        return evaluatedNodes;
    }
    void updateState(T state, T newCameFrom, double newCost){
        auto updatedState = openListMap->at(state);
        openList->erase(updatedState);
        updatedState->setCameFrom(newCameFrom);
        updatedState->setCost(newCost);
        openList->insert(updatedState);
    }
protected:
    State<T>* popOpenList(){
        evaluatedNodes++;
        auto top = openList->begin();
        openList->erase(top);
        openListMap->erase((*top)->getState());
        return *top;
    }
};
#endif //GENERICSOLVER_SEARCHER_H
