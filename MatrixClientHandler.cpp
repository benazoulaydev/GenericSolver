//
// Created by ben on 16/01/2020.
//

#include "MatrixClientHandler.h"


void MatrixClientHandler::handleClient(int socketFD, int outputStream) {
    //TODO add CacheManager feature
    //CacheManager<strinClass> my_2nd_cache(5);
    string line, sol;

    vector<int> row;
    vector<int> init_row;
    vector<int> goal_row;
    vector<int> matrixLine;


    vector<string> stringMatrix;

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
    init_row = split(stringMatrix.at(sizeMatrix), ',');
    goal_row = split(stringMatrix.at(sizeMatrix+1), ',');


    Cell *initCell = new Cell(init_row[0], init_row[1]);
    Cell *goalCell = new Cell(goal_row[0], goal_row[1]);
    cout<<"hi"<<endl;

    MatrixMaze *matrixMaze = new MatrixMaze(*initCell,*goalCell,&matrixLine, sizeMatrix);
    cout<<"hi"<<endl;






}


vector<int> MatrixClientHandler::split(string line, char c) {
    stringstream ss( line );
    vector<int> resultat;
    while( ss.good() )
    {
        string substr;
        getline( ss, substr, c );
        resultat.push_back( stoi(substr) );
    }
    return resultat;
}

