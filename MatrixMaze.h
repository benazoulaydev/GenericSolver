//
// Created by kfiry on 09/01/2020.
//

#ifndef GENERICSOLVER_MATRIXMAZE_H
#define GENERICSOLVER_MATRIXMAZE_H


#include "Searchable.h"
#include "Cell.h"
#include <utility>
using namespace std;

class MatrixMaze : public Searchable<Cell>{
private:
    double maze[2][2] = {{1,1},
                        {2,2}};
    State<Cell>* goal = nullptr;
    int size = 2;

public:
    State<Cell>* getInitState() override {
        return makeState(0,0, -1,-1, maze[0][0]);
    }

    vector<State<Cell>*>* getAllPossibleStates(State<Cell>* s) override {
        auto states = new vector<State<Cell>*>;
        int i = s->getState().getI(), j = s->getState().getJ();
        //check bounds
        if(j!=0) // left
            states->emplace_back(makeState(i,j-1,i,j, maze[i][j-1]));
        if(i!=0) // up
            states->emplace_back(makeState(i-1,j,i,j, maze[i-1][j]));
        if(j!=size-1) // right
            states->emplace_back(makeState(i,j+1,i,j, maze[i][j+1]));
        if(i!=size-1) // down
            states->emplace_back(makeState(i+1,j,i,j, maze[i+1][j]));
        return states;
    }

    bool isGoalState(State<Cell>* s) override {
        if(goal == nullptr){
            this->goal = makeState(size-1,size-1, size,size, maze[size-1][size-1]);
        }
        bool l = goal==s;
        cout<<s->getState().getI()<<s->getState().getJ()<<endl;
        return l;
    }
    State<Cell>* makeState(int i, int j, int cameI, int cameJ, double cost);
};

State<Cell> *MatrixMaze::makeState(int i, int j, int cameI, int cameJ, double cost){
    auto c1 = new Cell(i,j);
    auto c2 = new Cell(cameI,cameJ);
    return new State<Cell>(*c1, *c2, cost);
}


#endif //GENERICSOLVER_MATRIXMAZE_H