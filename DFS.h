//
// Created by kfiry on 13/01/2020.
//

#ifndef GENERICSOLVER_DFS_H
#define GENERICSOLVER_DFS_H

#include "ISearcher.h"
#include <stack>
#include <unordered_map>
using namespace std;

template <typename T> class DFS  : public ISearcher<T>{
    int idAlgo =6;
    stack<State<T>> S;
    unordered_map<T, pair<bool,State<T>*>> discovered;
    int evaluatedNodes;
public:
    /**
     * id of algo for hash name
     * @return
     */
    int getIdAlgo() {
        return idAlgo;
    }
    /**
     * the Dfs algo
     * @param s
     * @return
     */
    Solution<T> *search(Searchable<T> *s) override {
        vector<State<T> *> vec;
        vec.push_back(s->getInitState());
        stack<pair<State<T> *, vector<State<T> *>>> st;
        st.push(make_pair(s->getInitState(), vec));
        unordered_set<T> visited;
        while (!st.empty()) {
            auto vertex = st.top();
            st.pop();
            evaluatedNodes++;
            if (visited.find((vertex.first)->getState()) == visited.end()) {
                if (s->isGoalState(vertex.first)) {
                    return toSol(vertex.second);
                }
                visited.emplace((vertex.first)->getState());
                auto succerssors = s->getAllPossibleStates(vertex.first);
                for (State<T> *neib : *succerssors) {
                    vector<State<T> *> newVec = vertex.second;
                    newVec.push_back(neib);
                    st.push(make_pair(neib, newVec));
                }
            }
        }
        cout << "DFS failed" << endl;
    }
    /**
     * getNumberOfNodeEvaluated
     * @return the number of node evaluated
     */
    int getNumberOfNodeEvaluated() override {
        return evaluatedNodes;
    }
    /**
     * @param path
     * @return the solution
     */
    Solution<T> *toSol(vector<State<T>*> path){
        Solution<T>* solution = new Solution<T>();
        for(auto p:path){
            solution->addState(p->getState());
        }
        return solution;
    }
    ~DFS(){};

};


#endif //GENERICSOLVER_DFS_H
