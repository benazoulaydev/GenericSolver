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
    /**
     * add state for the solution
     * @param state
     */
    void addState(T state){
        path->emplace_back(state);
    }
    /**
     * add state to front
     * @param state
     */
    void addStateFront(T state){
        path->insert(path->begin(), state);
    }
    /**
     * @return the path
     */
    std::vector<T>* getPath(){
        return path;
    }
    ~Solution(){}

};
#endif //GENERICSOLVER_SOLUTION_H
