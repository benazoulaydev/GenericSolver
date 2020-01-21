//
// Created by kfiry on 09/01/2020.
//

#ifndef GENERICSOLVER_SEARCHABLE_H
#define GENERICSOLVER_SEARCHABLE_H

#include "State.h"
#include <vector>

template <typename T>
class Searchable {
public:
    /**
     * @return the initial cell where the algo begin
     */
    virtual State<T> * getInitState()=0;
    /**
     * all of the possible states
     * @param s
     * @return all of the possible states
     */
    virtual std::vector<State<T>*>* getAllPossibleStates(const State<T>* s)=0;
    /**
     * check if the cell is the goal cell
     * @param s
     * @return true or false
     */
    virtual bool isGoalState(const State<T>* s)=0;
    /**
     * @param state
     * @return the distance from goal
     */
    virtual double distanceFromGoal(State<T>* state)=0;
    /**
     * the direction for sending purpose
     * @param src
     * @param dst
     * @return string of direction of algo
     */
    virtual string direction(T src, T dst)=0;
    /**
     * the cost of a given cell
     * @param state
     * @return the cost
     */
    virtual int cost(T state)=0;
    virtual ~Searchable() {}

};


#endif //GENERICSOLVER_SEARCHABLE_H
