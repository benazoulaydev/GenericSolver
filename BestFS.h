//
// Created by kfiry on 16/01/2020.
//

#ifndef GENERICSOLVER_BESTFS_H
#define GENERICSOLVER_BESTFS_H
#include "ISearcher.h"
#include "Solution.h"
#include <bits/stdc++.h>
using namespace  std;
// better implemtation of the algorithm BestFirstSearch

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
    /**
     * add state to openSet Map
     * @param state
     */
    void addToOpenList(State<T>* state){
        openSet.emplace(state->getState(), *state);
        costMap.emplace(state->getCost(), *state);
    }
    bool openContains(T state){
        return openSet.find(state) != openSet.end();
    }
    /**
     * getNumberOfNodeEvaluated
     * @return the number of node evaluated
     */
    int getNumberOfNodeEvaluated() override {
        return evaluatedNodes;
    }
    /**
     * pop value from openList map
     * @return the new top
     */
    State<T>* popOpenList(){
        evaluatedNodes++;
        auto top = costMap.begin();
        auto newTop = &openSet.at(top->second.getState());
        costMap.erase(top);
        openSet.erase(newTop->getState());
        return newTop;
    }
    Solution<T>* search(Searchable<T>* searchable) override;

    virtual ~BestFS();
};


template<typename T>
/**
 * BestFs Algo
 * @tparam T
 * @param searchable
 * @return
 */
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
                delete s;
            }
        }
    }
    cout<<"bestFS did not work "<<getNumberOfNodeEvaluated()<<endl;
    return nullptr;
}


template<typename T>
/**
 * backTrace
 * @tparam T
 * @param goalState
 * @param init
 * @return the solution
 */
Solution<T> *BestFS<T>::backTrace(State<T> *goalState, State<T> *init) {
    Solution<T>* solution = new Solution<T>();
    State<T>* tempState;
    tempState = goalState;
    while(tempState->getState() != init->getState()){
        solution->addStateFront(tempState->getState());
        tempState = &closed.at(tempState->getCameFrom());
    }
    solution->addStateFront(tempState->getState());
    return solution;
}

template<typename T>
BestFS<T>::~BestFS() {
    for(auto i1=closed.begin();i1!=closed.end();i1++) {
        delete &i1->second;
    }
    for(auto i1=openSet.begin();i1!=openSet.end();i1++) {
        delete &i1->second;
    }
}


#endif //GENERICSOLVER_BESTFS_H
