//
// Created by kfiry on 13/01/2020.
//

#ifndef GENERICSOLVER_BFS_H
#define GENERICSOLVER_BFS_H

#include "ISearcher.h"
#include <queue>
#include <unordered_map>
using namespace std;

template <typename T> class BFS : public ISearcher<T>{
private:
    queue<State<T>> Q;
    unordered_map<T, pair<bool,State<T>*>> discovered;
    int evaluatedNodes;
public:

    int getNumberOfNodeEvaluated() override {
        return evaluatedNodes;
    }
    Solution<T> *Search(Searchable<T> *s) override {
        auto start = s->getInitState();
        Q.push(*start);
        while(!Q.empty()){
            State<T> v = Q.front();
            Q.pop();
            if(s->isGoalState(&v))
                return backTrace(&v,s->getInitState());
            auto succerssors = s->getAllPossibleStates(&v);
            for(State<T>* w : *succerssors){
                if(discovered.find(w->getState()) == discovered.end()){
                    discovered[w->getState()] = make_pair(false, w);
                }
                if(!discovered[w->getState()].first){
                    discovered[w->getState()].first = true;
                    w->setCameFrom(v.getState());
                    Q.push(*w);
                }
            }
        }
    }

    Solution<T> *backTrace(const State<T>* goalState, State<T> *init) {
        Solution<T>* solution = new Solution<T>();
        const State<T>* tempState;
        tempState = goalState;
        while(tempState->getState() != init->getState()){
            solution->addStateFront(tempState->getState());
            tempState = discovered[tempState->getCameFrom()].second;
        }
        solution->addStateFront(tempState->getState());
        return solution;
    }
};


#endif //GENERICSOLVER_BFS_H
