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
    std::vector<State<T>>* path;
public:
    Solution(){
        this->path = new std::vector<State<T>>;
    }
    void addState(State<T> state){
        path->emplace_back(state);
    }
    std::vector<State<T>>* getPath(){
        return path;
    }
};
#endif //GENERICSOLVER_SOLUTION_H
