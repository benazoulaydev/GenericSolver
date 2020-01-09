//
// Created by kfiry on 09/01/2020.
//

#ifndef GENERICSOLVER_SEARCHERINTERFACE_H
#define GENERICSOLVER_SEARCHERINTERFACE_H


#include "Searchable.h"
#include "Solution.h"

template <typename T>
class SearcherInterface {
public:
    virtual Solution<T>* Search(Searchable<T>* s)=0;
    virtual int getNumberOfNodeEvaluated()=0;
};


#endif //GENERICSOLVER_SEARCHERINTERFACE_H
