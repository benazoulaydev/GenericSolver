//
// Created by kfiry on 09/01/2020.
//

#ifndef GENERICSOLVER_SEARCHABLE_H
#define GENERICSOLVER_SEARCHABLE_H

#include "State.h"
#include <vector>

template <typename T>
class Searchable {
public:
    virtual State<T> * getInitState()=0;
    virtual std::vector<State<T>*>* getAllPossibleStates(const State<T>* s)=0;
    virtual bool isGoalState(const State<T>* s)=0;
    virtual string direction(T src, T dst)=0;
    virtual int cost(T state)=0;
};


#endif //GENERICSOLVER_SEARCHABLE_H
