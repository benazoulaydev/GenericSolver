//
// Created by kfiry on 09/01/2020.
//

#ifndef GENERICSOLVER_MATRIXMAZE_H
#define GENERICSOLVER_MATRIXMAZE_H


#include "Searchable.h"
#include "Cell.h"
#include <utility>
#include <cmath>
using namespace std;

class MatrixMaze : public Searchable<Cell>{
private:
    vector<int> maze;
    State<Cell>* init;
    State<Cell>* goal;
    int size;

public:
    MatrixMaze(Cell initCell, Cell goalCell, vector<int>* matrixMaze, int mazeSize){
        maze = *matrixMaze;
        init = new State<Cell>(initCell, *new Cell(-1,-1), cost(initCell.getI(),initCell.getJ()));
        goal = new State<Cell>(goalCell, *new Cell(size,size), cost(goalCell.getI(),goalCell.getJ()));
        size = mazeSize;
    }
    State<Cell>* getInitState() override {
        return init;
    }
    int cost(Cell state) override{
        return cost(state.getI(),state.getJ());
    }
    int cost(int i, int j){
        return maze[i*size+j];
    }
    string direction(Cell src, Cell dst) override{
        if(dst.getJ()-src.getJ() > 0)
            return "Right";
        if(dst.getJ()-src.getJ() < 0)
            return "Left";
        if(dst.getI()-src.getI() > 0)
            return "Down";
        if(dst.getI()-src.getI() < 0)
            return "Up";

    }
    vector<State<Cell>*>* getAllPossibleStates(const State<Cell>* s) override {
        auto states = new vector<State<Cell>*>;
        int i = s->getState().getI(), j = s->getState().getJ();
        //check bounds
        if(j!=0 && cost(i,j-1) != -1) // left
            states->emplace_back(makeState(i,j-1,i,j, cost(i,j-1)));
        if(i!=0 && cost(i-1,j) != -1) // up
            states->emplace_back(makeState(i-1,j,i,j, cost(i-1,j)));
        if(j!=size-1 && cost(i,j+1) != -1) // right
            states->emplace_back(makeState(i,j+1,i,j, cost(i,j+1)));
        if(i!=size-1 && cost(i+1,j) != -1) // down
            states->emplace_back(makeState(i+1,j,i,j, cost(i+1,j)));
        return states;
    }

    bool isGoalState(const State<Cell>* s) override {
        return goal->getState() == s->getState();
    }
    double distanceFromGoal(State<Cell>* state){
        int i = state->getState().getI(), j = state->getState().getJ();
        if(j!=0 && cost(i,j-1) != -1 && cost(i,j-1)==0) // left
            return 0;
        if(i!=0 && cost(i-1,j) != -1 && cost(i-1,j)==0) // up
            return 0;
        if(j!=size-1 && cost(i,j+1) != -1 && cost(i,j+1)) // right
            return 0;
        if(i!=size-1 && cost(i+1,j) != -1 && cost(i+1,j)) // down
            return 0;
        double dx = (i-(size-1));
        double dy = (j-(size-1));
        return sqrt(dx*dx)+sqrt(dy*dy);
    }
//    State<Cell>* getGoalState() override {
//        return makeState(size-1,size-1, -1,-1, maze[0][0]);
//    }

    State<Cell>* makeState(int i, int j, int cameI, int cameJ, double cost){
        auto c1 = new Cell(i,j);
        auto c2 = new Cell(cameI,cameJ);
        return new State<Cell>(*c1, *c2, cost);
    }
};

#endif //GENERICSOLVER_MATRIXMAZE_H
