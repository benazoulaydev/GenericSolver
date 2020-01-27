//
// Created by kfiry on 16/01/2020.
//

#ifndef GENERICSOLVER_ASTAR_H
#define GENERICSOLVER_ASTAR_H

#include "ISearcher.h"
#include "Solution.h"
#include "BFS.h"
#include <bits/stdc++.h>
#include <limits>
// better implemtation of the algorithm A*
template <typename T>
class AStar : public ISearcher<T> {
private:
    int idAlgo = 1;

    int evaluatedNodes=0;
    Searchable<T>* searchable;
    multimap<double, State<T>&> costMap;
    unordered_map<T, State<T>&> openSet;
    unordered_map<T, T> cameFrom;
    unordered_map<T, double> gScore;
    unordered_map<T, double> fScore;

public:
    void resetField(){
        evaluatedNodes = 0;
        costMap.clear();
        openSet.clear();
        cameFrom.clear();
        gScore.clear();
        fScore.clear();
    }
    /**
     * id of algo for hash name
     * @return
     */
    int getIdAlgo() {
        return idAlgo;
    }
    /**
     * getNumberOfNodeEvaluated
     * @return the number of node evaluated
     */
    int getNumberOfNodeEvaluated() override {
        return evaluatedNodes;
    }

    /**
    * Important!!! Only for matrix grid!!!!!
    * @param s
    * @return the distance to the goal
    */
    double h(State<T> &s){
        return searchable->distanceFromGoal(&s);
    }
    /**
     * A* algo
     * @param s
     * @return the solution
     */
    Solution<T>* search(Searchable<T>* s) override{
        searchable = s;
        // psuducode from wikipedia
        // The set of discovered nodes that may need to be (re-)expanded.
        // Initially, only the start node is known.
        State<T>* start = s->getInitState();
        addToOpen(start);
        // For node n, cameFrom[n] is the node immediately preceding it on the cheapest path from start to n currently known.

        // For node n, gScore[n] is the cost of the cheapest path from start to n currently known.
        //gScore := map with default value of Infinity
        gScore[start->getState()] = 0;

        // For node n, fScore[n] := gScore[n] + h(n).
        //fScore := map with default value of Infinity
        fScore[start->getState()] = h(*start);

        while(!openSet.empty()){
            //current := the node in openSet having the lowest fScore[] value
            State<T>* current = getCurrent();

            if (s->isGoalState(current)) {
                double totalCost = 0;
                T cur = current->getState();
                while(cameFrom.find(cur) != cameFrom.end()) {
                    totalCost+=s->cost(cur);
                    cur = cameFrom[cur];
                }
                return reconstruct_path(current);
            }
            evaluatedNodes++;
            openSet.erase(current->getState());
            for (State<T>* neighbor : *s->getAllPossibleStates(current)){
                T neighborState = neighbor->getState();
                // d(current,neighbor) is the weight of the edge from current to neighbor
                // tentative_gScore is the distance from start to the neighbor through current
                if(gScore.find(neighborState) == gScore.end())
                    gScore[neighborState] = numeric_limits<double>::infinity();
                if(fScore.find(neighborState) == fScore.end())
                    fScore[neighborState] = numeric_limits<double>::infinity();

                double tentative_gScore = gScore[current->getState()] + neighbor->getCost();
                if(tentative_gScore < gScore[neighborState]){
                    // This path to neighbor is better than any previous one. Record it!
                    cameFrom[neighborState] = current->getState();
                    gScore[neighborState] = tentative_gScore;
                    fScore[neighborState] = 2*gScore[neighborState] + h(*neighbor);
                    if(openSet.find(neighborState) == openSet.end())
                        addToOpen(neighbor);
                }
            }
        }
        // Open set is empty but goal was never reached
        cout<<"A* Failed"<<endl;
        return nullptr;
    }
    /**
     * current := the node in openSet having the lowest fScore[] value
     * @return current
     */
    State<T>* getCurrent(){
        auto top = costMap.begin();
        auto newTop = &openSet.at(top->second.getState());
        costMap.erase(top);
        openSet.erase(newTop->getState());
        return newTop;
    }
    /**
     * add state to openSet Map
     * @param state
     */
    void addToOpen(State<T>* state){
        openSet.emplace(state->getState(), *state);
        costMap.emplace(fScore[state->getState()], *state);
    }
    /**
    * the new path to solution
    * @param goal
    * @return the new path to solution
    */
    Solution<T> *reconstruct_path (State<T>* goal){
        T current = goal->getState();
        Solution<T>* total_path = new Solution<T>();
        while(cameFrom.find(current) != cameFrom.end()) {
            total_path->addStateFront(current);
            current = cameFrom[current];
        }
        total_path->addStateFront(searchable->getInitState()->getState());
        return total_path;
    }
    ~AStar(){};

};



#endif //GENERICSOLVER_ASTAR_H
