////
//// Created by kfiry on 06/01/2020.
////
//
//#include "MyTestClientHandler.h"
//#include <strings.h>
//#include <unistd.h>
//#include <sys/socket.h>
//#include <cstring>
//#include <algorithm>
//#include "strinClass.h"
//
//void MyTestClientHandler::handleClient(int socketFD, int outputStream) {
//
//    //TODO add CacheManager feature
//    while(true){
//
//
//        cout<<"---------"<<"Done"<<endl;
//        const char *toSend = "D";
//        char buffer[4096] = {0};
//        bzero(buffer, 4096);
//        int n = read(socketFD , buffer, 4096);
//        std::string strInput(buffer), strEnd("end");
//        strInput.erase(std::remove_if(strInput.begin(), strInput.end(), ::isspace), strInput.end());
//        if(strInput.compare(strEnd) == 0){
//            close(socketFD);
//            return;
//        }
//        try {
//            if (cm->check(strInput)) {
//                strinClass emp1 = cm->get(strInput);
//                cout <<"success"<< strInput<<endl;
//                emp1.print();
//            } else {
//                cout <<"key does not exist"<<endl;
//                //copy strinput string
//                std::string strProblem(strInput);
//
//                std::string s = solver->solve(&strInput);
//                toSend = s.c_str();
//
//
//                int isSent = send(outputStream, toSend, s.size(), 0);
//                if (isSent == -1) {
//                    std::cout<<"Error sending message"<<std::endl;
//                }
//
//                try {
//                    cout <<strProblem<<endl;
//                    cm->insert(strProblem, strinClass(s.c_str()));
//                } catch  (const char * e) {
//                    cout << e << endl;
//                }
//
//            }
//
//        } catch (const char * e) {
//            cout <<"error"<<endl;
//        }
//
//
//
//    }
//}
