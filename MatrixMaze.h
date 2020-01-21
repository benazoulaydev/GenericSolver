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
        size = mazeSize;
        init = new State<Cell>(initCell, *new Cell(-1,-1), cost(initCell.getI(),initCell.getJ()));
        goal = new State<Cell>(goalCell, *new Cell(size,size), cost(goalCell.getI(),goalCell.getJ()));
    }
    /**
     * @return the initial cell where the algo begin
     */
    State<Cell>* getInitState() override {
        return init;
    }
    /**
     * the cost of a given cell
     * @param state
     * @return the cost
     */
    int cost(Cell state){
        return cost(state.getI(),state.getJ());
    }
    /**
     * the cost in the matrix at i,j
     * @param i
     * @param j
     * @return
     */
    int cost(int i, int j){
        return maze[i*size+j];
    }
    /**
     * the direction for sending purpose
     * @param src
     * @param dst
     * @return string of direction of algo
     */
    string direction(Cell src, Cell dst) override{
        if(dst.getJ()-src.getJ() > 0)
            return "Right";
        if(dst.getJ()-src.getJ() < 0)
            return "Left";
        if(dst.getI()-src.getI() > 0)
            return "Down";
        if(dst.getI()-src.getI() < 0)
            return "Up";
        return "";
    }
    /**
     * all of the possible states
     * @param s
     * @return all of the possible states
     */
    vector<State<Cell>*>* getAllPossibleStates(const State<Cell>* s) override {
        auto states = new vector<State<Cell>*>;
        int i = s->getState().getI(), j = s->getState().getJ();
        //chek validity
        if(i>size-1 || i<0 ||j<0 || i>size-1){
            cout<<"undefined Cell"<<endl;
            throw "Error in Cell";
        }
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
    /**
     * check if the cell is the goal cell
     * @param s
     * @return true or false
     */
    bool isGoalState(const State<Cell>* s) override {
        return goal->getState() == s->getState();
    }
    /**
     * @param state
     * @return the distance from goal
     */
    double distanceFromGoal(State<Cell>* state){
        double dx = (state->getState().getI()-(size-1));
        double dy = (state->getState().getJ()-(size-1));
        return sqrt(dx*dx+dy*dy);
    }
    /**
     * create a new state
     * @param i
     * @param j
     * @param cameI
     * @param cameJ
     * @param cost
     * @return the state created
     */
    State<Cell>* makeState(int i, int j, int cameI, int cameJ, double cost){
        auto c1 = new Cell(i,j);
        auto c2 = new Cell(cameI,cameJ);
        return new State<Cell>(*c1, *c2, cost);
    }
    ~MatrixMaze(){}

};

#endif //GENERICSOLVER_MATRIXMAZE_H
