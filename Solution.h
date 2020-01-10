//
// Created by kfiry on 09/01/2020.
//

#ifndef GENERICSOLVER_SOLUTION_H
#define GENERICSOLVER_SOLUTION_H

#include "State.h"
#include<vector>

template <typename T>
class Solution{
private:
    std::vector<T>* path;
public:
    Solution(){
        this->path = new std::vector<T>;
    }
    void addState(T state){
        path->emplace_back(state);
    }
    void addStateFront(T state){
        path->insert(path->begin(), state);// emplace_back(state);
    }
    std::vector<T>* getPath(){
        return path;
    }
};
#endif //GENERICSOLVER_SOLUTION_H
