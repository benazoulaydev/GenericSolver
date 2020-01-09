//
// Created by kfiry on 06/01/2020.
//

#include <strings.h>
#include <unistd.h>
#include <sys/socket.h>
#include <cstring>
#include <algorithm>
#include "MyTestClientHandler.h"

void MyTestClientHandler::handleClient(int socketFD, int outputStream) {
    //TODO add CacheManager feature
    while(true){
        char buffer[4096] = {0};
        bzero(buffer, 4096);
        int n = read(socketFD , buffer, 4096);
        std::string strInput(buffer), strEnd("end");
        strInput.erase(std::remove_if(strInput.begin(), strInput.end(), ::isspace), strInput.end());
        if(strInput.compare(strEnd) == 0){
            close(socketFD);
            return;
        }
        std::string s = solver->solve(strInput);
        const char *toSend = s.c_str();
        int isSent = send(outputStream, toSend, s.size(), 0);
        if (isSent == -1) {
            std::cout<<"Error sending message"<<std::endl;
        }
    }
}
