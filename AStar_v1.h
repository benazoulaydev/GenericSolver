//
// Created by kfiry on 14/01/2020.
//

#ifndef GENERICSOLVER_ASTAR_V1_H
#define GENERICSOLVER_ASTAR_V1_H
// naive implemtation of A*
#include "ISearcher.h"
#include "Solution.h"
#include "BFS.h"
#include <bits/stdc++.h>
#include <limits>
template <typename T>
class AStar_v1 : public ISearcher<T> {
private:
    int idAlgo =2;
    int evaluatedNodes=0;
    Searchable<T>* searchable;
    unordered_map<T, State<T>&> openSet;
    unordered_map<T, T> cameFrom;
    unordered_map<T, double> gScore;
    unordered_map<T, double> fScore;
public:
    /**
 * clone function.
 * @tparam T
 * @return the clone
 */
    ISearcher<T> *clone() override {
        return new AStar_v1<T>{};
    }

    void resetField(){
        evaluatedNodes = 0;
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
     *
     * @param s
     * @return the distance to the goal
     */
    double h(State<T> &s){
        BFS<T> bfs{};
        double d = bfs.absDistance(searchable, s);
        return d;
    }
    /**
     * A* algo
     * @param s
     * @return the solution
     */
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
                double totalCost = 0;
                T cur = current->getState();
                while(cameFrom.find(cur) != cameFrom.end()) {
                    totalCost+=s->cost(cur);
                    cur = cameFrom[cur];
                }
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
    /**
     * current := the node in openSet having the lowest fScore[] value
     * @return current
     */
    State<T>* getCurrent(){
        State<T>* current = &openSet.begin()->second;
        for(auto pair: openSet){
            if(fScore[pair.first] < fScore[current->getState()]) {
                current = &pair.second;
            }
        }
        return current;
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
        return total_path;
    }
    ~AStar_v1(){};
};


#endif //GENERICSOLVER_ASTAR_V1_H
