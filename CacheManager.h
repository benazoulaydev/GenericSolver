//
// Created by kfiry on 08/01/2020.
//

#ifndef GENERICSOLVER_CACHEMANAGER_H
#define GENERICSOLVER_CACHEMANAGER_H
#include <string>

using namespace std;

template <typename  T> class CacheManager {
public:
    /**
     * check if problem exist and return boolean
     * @param key
     * @return
     */
    virtual bool check(string key) = 0;
    /**
     * insert new value to cache
     * @param key
     * @param value
     */
    virtual void insert(string key, T value) = 0;
    /**
     * get the value with the given key from cache
     * @param key
     * @return
     */
    virtual T get(string key) = 0;
    virtual ~CacheManager(){};

};


#endif //GENERICSOLVER_CACHEMANAGER_H
