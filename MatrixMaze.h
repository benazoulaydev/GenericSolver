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
    int **maze;
    State<Cell>* init;
    State<Cell>* goal;
    int size;

public:
    MatrixMaze(Cell initCell, Cell goalCell, int **matrixMaze, int mazeSize){
        init = new State<Cell>(initCell, *new Cell(-1,-1), maze[initCell.getI()][initCell.getJ()]);
        goal = new State<Cell>(goalCell, *new Cell(size,size), maze[goalCell.getI()][goalCell.getJ()]);
        maze = matrixMaze;
        size = mazeSize;
    }
    State<Cell>* getInitState() override {
        return init;
    }
    double cost(Cell state){
        return maze[state.getI()][state.getJ()];
    }

    vector<State<Cell>*>* getAllPossibleStates(const State<Cell>* s) override {
        auto states = new vector<State<Cell>*>;
        int i = s->getState().getI(), j = s->getState().getJ();
        //check bounds
        if(j!=0 && maze[i][j-1] != -1) // left
            states->emplace_back(makeState(i,j-1,i,j, maze[i][j-1]));
        if(i!=0 && maze[i-1][j] != -1) // up
            states->emplace_back(makeState(i-1,j,i,j, maze[i-1][j]));
        if(j!=size-1 && maze[i][j+1] != -1) // right
            states->emplace_back(makeState(i,j+1,i,j, maze[i][j+1]));
        if(i!=size-1 && maze[i+1][j] != -1) // down
            states->emplace_back(makeState(i+1,j,i,j, maze[i+1][j]));
        return states;
    }

    bool isGoalState(const State<Cell>* s) override {
        return goal->getState() == s->getState();
    }
    State<Cell>* makeState(int i, int j, int cameI, int cameJ, double cost){
        auto c1 = new Cell(i,j);
        auto c2 = new Cell(cameI,cameJ);
        return new State<Cell>(*c1, *c2, cost);
    }
};
#endif //GENERICSOLVER_MATRIXMAZE_H
