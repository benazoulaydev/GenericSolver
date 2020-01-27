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
    /**
     * search given a searchable for the solution
     * @param s
     * @return the solution
     */
    virtual Solution<T>* search(Searchable<T>* s)=0;
    /**
     * @return the number of node evaluated with algo
     */
    virtual int getNumberOfNodeEvaluated()=0;
    virtual int getIdAlgo()=0;
    virtual void resetField()=0;
    virtual ~ISearcher() {}

};


#endif //GENERICSOLVER_ISEARCHER_H
