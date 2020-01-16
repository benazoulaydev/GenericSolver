//
// Created by kfiry on 16/01/2020.
//

#ifndef GENERICSOLVER_BESTFS2_H
#define GENERICSOLVER_BESTFS2_H

#include "ISearcher.h"
#include "Solution.h"
#include <bits/stdc++.h>
using namespace  std;

template <typename T>
class BestFS2 : public ISearcher<T>{
private:
    multimap<double, State<T>&> costMap;
    unordered_map<T, State<T>&> openSet;
    priority_queue<State<T>> PQ;
    unordered_map<T, State<T>&> closed;
    int evaluatedNodes = 0;
    Solution<T> *backTrace(State<T>* goalState, State<T> *init);
    Searchable<T>* searchableI;
public:
    void addToOpenList(State<T>* state){
        openSet.emplace(state->getState(), *state);
//        costMap.emplace(state->getCost(), *state);
        PQ.push(*state);
    }
    bool openContains(T state){
        return openSet.find(state) != openSet.end();
    }
    int getNumberOfNodeEvaluated() override {
        return evaluatedNodes;
    }
    State<T>* popOpenList(){
        evaluatedNodes++;
        auto top = &PQ.top();
        auto top2 = &openSet.at(top->getState());
        openSet.erase(top->getState());
        PQ.pop();
        return top2;
    }
    Solution<T>* search(Searchable<T>* searchable) override;
};


template<typename T>
Solution<T> *BestFS2<T>::search(Searchable<T>* searchable) {
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
Solution<T> *BestFS2<T>::backTrace(State<T> *goalState, State<T> *init) {
    Solution<T>* solution = new Solution<T>();
    State<T>* tempState;
    tempState = goalState;
    double totalCost = 0;
    while(tempState->getState() != init->getState()){
        totalCost+=searchableI->cost(tempState->getState());
        solution->addStateFront(tempState->getState());
        tempState = &closed.at(tempState->getCameFrom());
    }
    cout<<totalCost<<endl;
//    solution->addStateFront(tempState->getState());
    return solution;
}



#endif //GENERICSOLVER_BESTFS2_H
