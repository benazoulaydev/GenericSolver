//
// Created by kfiry on 09/01/2020.
//

#ifndef GENERICSOLVER_STATE_H
#define GENERICSOLVER_STATE_H

template <typename T>
class State {
private:
    T state;
    State* cameFrom;
    double cost;
public:
    State(T s, State* cameF, double c){
        this->state = s;
        this->cameFrom = cameF;
        this->cost = c;
    }
    friend bool operator==(const State &lhs, const State &rhs) {
        return (lhs.w == rhs.w);
    }
    friend bool operator!=(const State &lhs, const State &rhs) {
        return !(lhs == rhs);
    }

    T getState() const {
        return state;
    }
};


#endif //GENERICSOLVER_STATE_H
