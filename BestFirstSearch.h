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
    unordered_map<T, State<T>>* closed;
    Solution<T> *backTrace(const State<T>* goalState, State<T> *init);
public:
    Solution<T>* Search(Searchable<T>* searchable) override;
    void printState(const State<T> *f,const State<T> *s);
};

template<typename T>
Solution<T> *BestFirstSearch<T>::Search(Searchable<T>* searchable) {
    Searcher<T>::addToOpenList(searchable->getInitState());
    closed = new unordered_map<T, State<T>>();
    while(Searcher<T>::openListSize() > 0){
        const State<T>* n = this->popOpenList();
        closed->emplace(n->getState(), *n);
        for (auto i : *closed){
            cout << i.second.getState().getI()<<i.second.getState().getJ()<<"-"<<i.second.getCost()<<" ";
        }
        cout<<"closed"<< endl;

        if(searchable->isGoalState(n)){
            return backTrace(n,searchable->getInitState()); // find the best path from the openList;
        }
        auto succerssors = searchable->getAllPossibleStates(n);
        for(State<T>* s : *succerssors){
//            cout<<"new cost-"<<s->getState().getI()<<","<<s->getState().getJ()<<" "<<
//                s->getCost()<<"+"<<n->getState().getI()<<","<<n->getState().getJ()<<" "<<n->getCost()<<endl;
            printState(s,n);
            s->setCost(s->getCost()+n->getCost());
            printState(s,n);
            if(closed->find(s->getState()) == closed->end() && !Searcher<T>::openContains(s->getState())){
                Searcher<T>::addToOpenList(s);
            } else {
                if(Searcher<T>::openContains(s->getState())){
                    double newCost = s->getCost();
//                    cout<<s->getCost()<<" "<<Searcher<T>::costToState(s->getState())<<endl;
                    if(newCost < Searcher<T>::costToState(s->getState())){
                        Searcher<T>::updateState(s->getState(), n->getState(), newCost);
                    }
                }else{
                    Searcher<T>::addToOpenList(s);
//                    double newCost = s->getCost();
//                    auto sd = closed->at(s->getState());
//                    if(newCost < sd.getCost()){
////                        printState(s,&sd);
////                        cout<<"hello"<<newCost <<"::"<< sd.getCost()<<endl;
//                        sd.setCost(newCost);
//                        sd.setCameFrom(n->getState());
//                    }
                }
            }
        }
    }
    cout<<"bestFS did not work "<<Searcher<T>::getNumberOfNodeEvaluated()<<endl;
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
    return solution;
}
template<typename T>
void BestFirstSearch<T>::printState(const State<T> *f,const State<T> *s){
    cout<<"1:";f->getState().printS();cout<<"cost:"<<f->getCost()
    <<";2:";s->getState().printS();cout<<"cost:"<<s->getCost()<<endl;
}
#endif //GENERICSOLVER_BESTFIRSTSEARCH_H
