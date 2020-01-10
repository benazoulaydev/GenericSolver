//
// Created by kfiry on 09/01/2020.
//

#ifndef GENERICSOLVER_STATE_H
#define GENERICSOLVER_STATE_H

template <typename T>
class State {
private:
    T state;
    T cameFrom;
    double cost;
public:
    State(T s, T cameF, double c){
        this->state = s;
        this->cameFrom = cameF;
        this->cost = c;
    }

    T getCameFrom() const {
        return cameFrom;
    }

    double getCost() const {
        return cost;
    }
    bool operator==(const State *rhs)const {
        return (this->getState() == rhs->getState());
    }
    bool operator!=(const State *rhs) const{
        return !(*this == *rhs);
    }
     bool operator<(const State *rhs)const{
        return this->cost < rhs->cost;
    }

    void setCameFrom(T from) {
        State::cameFrom = from;
    }

    void setCost(double c) {
        State::cost = c;
    }

    T getState() const {
        return state;
    }
};


#endif //GENERICSOLVER_STATE_H
