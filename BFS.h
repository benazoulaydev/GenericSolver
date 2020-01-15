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
    bool fromStart = true;
    State<T>* initState;
public:

    int getNumberOfNodeEvaluated() override {
        return evaluatedNodes;
    }
    Solution<T> *search(Searchable<T> *s) override {
        if(fromStart)
            initState = s->getInitState();
        Q.push(*initState);
        while(!Q.empty()){
            State<T> v = Q.front();
            Q.pop();
            evaluatedNodes++;
            if(s->isGoalState(&v))
                return backTrace(&v,initState);
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

    int absDistance(Searchable<T> *s, State<T> &init){
        fromStart = false;
        initState = &init;
        return search(s)->getPath()->size() - 1;
    }
};


#endif //GENERICSOLVER_BFS_H
