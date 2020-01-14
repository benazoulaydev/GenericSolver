//
// Created by kfiry on 14/01/2020.
//

#ifndef GENERICSOLVER_ASTAR_H
#define GENERICSOLVER_ASTAR_H

#include "ISearcher.h"
#include "Solution.h"
#include "BFS.h"
#include <bits/stdc++.h>
#include <limits>
template <typename T>

class AStar : public ISearcher<T> {
private:
    int evaluatedNodes;
    Searchable<T>* searchable;
    unordered_map<T, State<T>&> openSet;
    unordered_map<T, T> cameFrom;
    unordered_map<T, double> gScore;
    unordered_map<T, double> fScore;
public:
    int getNumberOfNodeEvaluated() override {
        return evaluatedNodes;
    }
    double h(State<T> &s){
        BFS<T> bfs{};
        double d = bfs.absDistance(searchable, s);
        return d;
    }
    Solution<T>* search(Searchable<T>* s) override{
        searchable = s;
        // The set of discovered nodes that may need to be (re-)expanded.
        // Initially, only the start node is known.
        State<T>* start = s->getInitState();
        openSet.emplace(start->getState(), *start);
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
                return reconstruct_path(current);
            }

            evaluatedNodes++;
//            for(auto i:openSet){
//                i.first.printS();
//            }
//            current->getState().printS();
//            cout<<evaluatedNodes<<endl;

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
                    fScore[neighborState] = gScore[neighborState] + h(*neighbor);
                    if(openSet.find(neighborState) == openSet.end())
                        openSet.emplace(neighborState, *neighbor);
                }
            }
        }
        // Open set is empty but goal was never reached
        cout<<"A* Failed"<<endl;
    }
    //current := the node in openSet having the lowest fScore[] value
    State<T>* getCurrent(){
        State<T>* current = &openSet.begin()->second;
//        current->getState().printS();
//        cout<<evaluatedNodes<<endl;
        for(auto pair: openSet){
            if(fScore[pair.first] < fScore[current->getState()]) {
                current = &pair.second;
            }
        }
//        cout<<evaluatedNodes<<endl;
        return current;
    }

    Solution<T> *reconstruct_path (State<T>* goal){
//        cout<<"enddddd"<<endl;
        T current = goal->getState();
        Solution<T>* total_path = new Solution<T>();
        while(cameFrom.find(current) != cameFrom.end()) {
            total_path->addStateFront(current);
            current = cameFrom[current];
        }
        return total_path;
    }
};


#endif //GENERICSOLVER_ASTAR_H
