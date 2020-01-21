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
    /**
     * the dad cell
     * @return
     */
    T getCameFrom() const {
        return cameFrom;
    }
    /**
     * the cost of the cell
     * @return cost
     */
    double getCost() const {
        return cost;
    }
    /**
     * overloadind operator == for comparing the cost
     * @param rhs
     * @return bool
     */
    bool operator==(const State &rhs)const {
        return getCost() == rhs.getCost();
//                return (getState() == rhs.getState());
    }
    /**
     * overloadind operator != for comparing the cost
     * @param rhs
     * @return bool
     */
    bool operator!=(const State &rhs) const{
        return !(*this == rhs);
    }
    /**
     * overloadind operator < for comparing the cost
     * @param rhs
     * @return bool
     */
    bool operator<(const State &rhs)const{
        return cost < rhs.cost;
    }
//    friend bool operator==(const State as, const State cs){
//        return (as.getState() == cs.getState());
//    }
    /**
     * set the dad cell
     * @param from
     */
    void setCameFrom(T from) {
        State::cameFrom = from;
    }
    /**
     * set the cost of the current cell
     * @param c
     */
    void setCost(double c) {
        State::cost = c;
    }
    /**
     * get the state of the current cell
     */
    T getState() const {
        return state;
    }
    ~State(){}

};


#endif //GENERICSOLVER_STATE_H
