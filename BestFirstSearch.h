//
// Created by kfiry on 09/01/2020.
//

#ifndef GENERICSOLVER_BESTFIRSTSEARCH_H
#define GENERICSOLVER_BESTFIRSTSEARCH_H

#include "Searcher.h"
#include "Solution.h"

template <typename T>
class BestFirstSearch : public Searcher<T>{
private:

public:

    Solution<T>* Search(Searchable<T>* searchable) override;
};

template<typename T>
Solution<T> *BestFirstSearch<T>::Search(Searchable<T>* searchable) {
    return nullptr;
}

#endif //GENERICSOLVER_BESTFIRSTSEARCH_H
