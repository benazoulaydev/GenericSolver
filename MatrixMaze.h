//
// Created by kfiry on 09/01/2020.
//

#ifndef GENERICSOLVER_MATRIXMAZE_H
#define GENERICSOLVER_MATRIXMAZE_H


#include "Searchable.h"
#include <utility>
using namespace std;

class MatrixMaze : public Searchable<pair<int,int>>{
private:
    double maze[3][3] = {{1,1,1},
                      {2,2,1},
                      {3,3,1}};
    State<pair<int,int>>* goal = nullptr;
    int size = 3;

public:
    State<pair<int,int>>* getInitState() override {
        return makeState(0,0, nullptr, maze[0][0]);
    }

    vector<State<pair<int,int>>*>* getAllPossibleStates(State<pair<int,int>>* s) override {
        auto states = new vector<State<pair<int,int>>*>;
        int i = s->getState().first, j = s->getState().second;
        //check bounds
        if(j!=0) // left
            states->emplace_back(makeState(i,j-1,s, maze[i][j-1]));
        if(i!=0) // up
            states->emplace_back(makeState(i-1,j,s, maze[i-1][j]));
        if(j!=size-1) // right
            states->emplace_back(makeState(i,j+1,s, maze[i][j+1]));
        if(i!=size-1) // down
            states->emplace_back(makeState(i+1,j,s, maze[i+1][j]));
        return states;
    }

    bool isGoalState(State<pair<int,int>>* s) override {
        if(goal == nullptr){
            this->goal = makeState(size-1,size-1, nullptr, maze[size-1][size-1]);
        }
        return *goal==*s;
    }
    State<pair<int,int>>* makeState(int i, int j, State<pair<int, int>>* cameFrom, double cost);
};

State<pair<int, int>> *MatrixMaze::makeState(int i, int j, State<pair<int, int>>* cameFrom, double cost){
    return new State<pair<int,int>>(make_pair(i,j), cameFrom, cost);
}


#endif //GENERICSOLVER_MATRIXMAZE_H
