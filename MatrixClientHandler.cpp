//
// Created by ben on 16/01/2020.
//

#include "MatrixClientHandler.h"
#include "BestFS.h"
#include "AStar.h"
#include "BFS.h"
#include "DFS.h"

/**
 * handle client for matrix input by client
 * @param socketFD
 * @param outputStream
 */
void MatrixClientHandler::handleClient(int socketFD, int outputStream) {
    //TODO add CacheManager feature
    //CacheManager<strinClass> my_2nd_cache(5);
    string line, sol;

    vector<int> row;
    vector<int> init_row;
    vector<int> goal_row;
    vector<int> matrixLine;
    string matrixStr = "";

    vector<string> stringMatrix;

    hash<string> hashKey;

    Cell p;
    int sizeMatrix = 0;
    vector<vector<int> > matrix;
    do {
        char buffer[1024];
        bzero(&buffer, sizeof(buffer));
        read(socketFD, &buffer, sizeof(buffer));
        string s = buffer;
        size_t pos = s.find('\n');
        line = s.substr(0, pos);
        //remove spaces
        line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());

        if (line.empty() || line == "end") {
            continue;
        }
        stringMatrix.push_back(line);
        matrixStr += line;
        matrixStr += '\n';

        sizeMatrix++;

    }
    while (line != "end");
    //we remove the 2 last lines (init, goal)
    sizeMatrix -=2;
    for(int i = 0; i< sizeMatrix; i++) {

        row = split(stringMatrix.at(i), ',');
        matrix.push_back(row);
        for(int j = 0; j< sizeMatrix; j++) {
            matrixLine.push_back(row.at(j));
        }

    }
    //create hash string from problem string to minimize the size file name

    auto hashed = hashKey(matrixStr);
    string keyHashed = to_string(hashed);
    string finalSolution;
    if (cm->check(keyHashed)) {
        cout << "key exist" << endl;

        finalSolution = cm->get(keyHashed);

    }else {
        cout << "key does not exist" << endl;
        init_row = split(stringMatrix.at(sizeMatrix), ',');
        goal_row = split(stringMatrix.at(sizeMatrix+1), ',');


        Cell *initCell = new Cell(init_row[0], init_row[1]);
        Cell *goalCell = new Cell(goal_row[0], goal_row[1]);

        MatrixMaze *matrixMaze = new MatrixMaze(*initCell,*goalCell,&matrixLine, sizeMatrix);
        finalSolution = SearchSolver(new BestFS<Cell>()).solve(matrixMaze);
        try {
            cm->insert(keyHashed, finalSolution);
        } catch  (const char * e) {
            cout << e << endl;
        }
    }



    int isSent = send(outputStream, finalSolution.c_str(), finalSolution.size(), 0);
    if (isSent == -1) {
        std::cout<<"Error sending message"<<std::endl;
    }
}

/**
 * create vector of a given string
 * @param line
 * @param c
 * @return
 */
vector<int> MatrixClientHandler::split(string line, char c) {
    stringstream ss( line );
    vector<int> result;
    while( ss.good() )
    {
        string substr;
        getline( ss, substr, c );
        result.push_back( stoi(substr) );
    }
    return result;
}

