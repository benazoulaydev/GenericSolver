//
// Created by kfiry on 12/01/2020.
//

#ifndef GENERICSOLVER_CUSTOM_PRIORITY_QUEUE_H
#define GENERICSOLVER_CUSTOM_PRIORITY_QUEUE_H


#include <queue>
#include <algorithm>

template<typename T>
class custom_priority_queue : public std::priority_queue<T, std::vector<T>>
{
public:

bool remove(const T& value) {
    auto it = std::find(this->c.begin(), this->c.end(), value);
    if (it != this->c.end()) {
        this->c.erase(it);
        std::make_heap(this->c.begin(), this->c.end(), this->comp);
        return true;
    }
    else {
        return false;
    }
}
};

#endif //GENERICSOLVER_CUSTOM_PRIORITY_QUEUE_H