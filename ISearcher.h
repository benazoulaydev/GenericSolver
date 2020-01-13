//
// Created by kfiry on 09/01/2020.
//

#ifndef GENERICSOLVER_ISEARCHER_H
#define GENERICSOLVER_ISEARCHER_H


#include "Searchable.h"
#include "Solution.h"

template <typename T>
class ISearcher {
public:
    virtual Solution<T>* Search(Searchable<T>* s)=0;
    virtual int getNumberOfNodeEvaluated()=0;
};


#endif //GENERICSOLVER_ISEARCHER_H
