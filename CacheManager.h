//
// Created by kfiry on 08/01/2020.
//

#ifndef GENERICSOLVER_CACHEMANAGER_H
#define GENERICSOLVER_CACHEMANAGER_H
#include <string>

using namespace std;

template <typename  T> class CacheManager {
public:
    //check if problem exist and return it
    virtual bool check(string key) = 0;
    virtual void insert(string key, T value) = 0;
    virtual T get(string key) = 0;
};


#endif //GENERICSOLVER_CACHEMANAGER_H
