//
// Created by ben on 16/01/2020.
//

#include "MatrixClientHandler.h"


void MatrixClientHandler::handleClient(int socketFD, int outputStream) {
    //TODO add CacheManager feature
    //CacheManager<strinClass> my_2nd_cache(5);
    string line, sol;
    int i=0, j;
    double cost;
    State<Cell>* node;
    vector<string> row;
    vector<string> stringMatrix;
    string matrixProblem;
    vector<State<Cell>*> tempR;
    vector<State<Cell>*> initGoalNode;
    vector<vector<State<Cell>*>> tempMatrix;
    Cell p;
    do {
        char buffer[1024];
        bzero(&buffer, sizeof(buffer));
        read(socketFD, &buffer, sizeof(buffer));
        string s = buffer;
        size_t pos = s.find('\n');
        line = s.substr(0, pos);
        if (line.empty() || line == "end") {
            continue;
        }
        stringMatrix.push_back(line);
    }
    while (line != "end");
        //int isSent = send(outputStream, toSend, s.size(), 0);
//        if (isSent == -1) {
//            std::cout<<"Error sending message"<<std::endl;
//        }

    std::cout<<"Error sending message"<<std::endl;

}