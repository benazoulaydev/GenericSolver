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
    virtual std::vector<State<T>*>* getAllPossibleStates(State<T>* s)=0;
    virtual bool isGoalState(State<T>* s)=0;
};


#endif //GENERICSOLVER_SEARCHABLE_H
