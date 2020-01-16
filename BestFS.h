//
// Created by kfiry on 16/01/2020.
//

#ifndef GENERICSOLVER_BESTFS_H
#define GENERICSOLVER_BESTFS_H
#include "ISearcher.h"
#include "Solution.h"
#include <bits/stdc++.h>
using namespace  std;

template <typename T>
class BestFS : public ISearcher<T>{
private:
    multimap<double, State<T>&> costMap;
    unordered_map<T, State<T>&> openSet;
    unordered_map<T, State<T>&> closed;
    int evaluatedNodes = 0;
    Solution<T> *backTrace(State<T>* goalState, State<T> *init);
    Searchable<T>* searchableI;
public:
    void addToOpenList(State<T>* state){
        openSet.emplace(state->getState(), *state);
        costMap.emplace(state->getCost(), *state);
    }
    bool openContains(T state){
        return openSet.find(state) != openSet.end();
    }
//    double costToState(T state){
//        double cost = 0;
//        if(openListMap->find(state) != openListMap->end())
//            cost = (openListMap->at(state))->getCost();
//        if(closed->find(state) != closed->end())
//            cost = (closed->at(state))->getCost();
//        return cost;
//    }
    int getNumberOfNodeEvaluated() override {
        return evaluatedNodes;
    }
//    void updateState(T state, T newCameFrom, double newCost){
//        State<T>* updatedState = openListMap->at(state);
//        updatedState->setCameFrom(newCameFrom);
//        updatedState->setCost(newCost);
//        openList->erase(*updatedState);
//        openList->emplace(*updatedState);
//    }
    State<T>* popOpenList(){
        evaluatedNodes++;
//        State<T>* current = &openSet.begin()->second;
//        for(auto pair: openSet){
//            if(pair.second.getCost() < current->getCost()) {
//                current = &pair.second;
//            }
//        }
//        openSet.erase(current->getState());
//        return current;

        auto top = costMap.begin();
        auto newTop = &openSet.at(top->second.getState());
        costMap.erase(top);
        openSet.erase(newTop->getState());
        return newTop;
    }
    Solution<T>* search(Searchable<T>* searchable) override;
};


template<typename T>
Solution<T> *BestFS<T>::search(Searchable<T>* searchable) {
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
//                double newCost = s->getCost();
//                if(newCost < costToState(s->getState())){
//                    if(!openContains(s->getState())){
//                        addToOpenList(s);
//                    }else {
////                        cout<<"hi"<<endl;
//                        updateState(s->getState(), n->getState(), newCost);
//                    }
//                }
            }
        }
    }
    cout<<"bestFS did not work "<<getNumberOfNodeEvaluated()<<endl;
}


template<typename T>
Solution<T> *BestFS<T>::backTrace(State<T> *goalState, State<T> *init) {
    Solution<T>* solution = new Solution<T>();
    State<T>* tempState;
    tempState = goalState;
    while(tempState->getState() != init->getState()){
        solution->addStateFront(tempState->getState());
        tempState = &closed.at(tempState->getCameFrom());
    }
    return solution;
}



#endif //GENERICSOLVER_BESTFS_H
