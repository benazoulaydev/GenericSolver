//
// Created by kfiry on 06/01/2020.
//
#include <thread>
#include <netinet/in.h>
#include <unistd.h>


#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <errno.h>
#include <cstring>

#include "MySerialServer.h"

void MySerialServer::open(int port, ClientHandler* c) {
    std::thread thread1(&MySerialServer::start,this, port, c);
    thread1.detach();
}

int MySerialServer::start(int port, ClientHandler* c) {



    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int rc;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello from server\n";
    struct timeval timeout;
    fd_set master_set, working_set;

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    // Forcefully attaching socket to the port given
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt))){
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    /*************************************************************/
    /* Set socket to be nonblocking. All of the sockets for      */
    /* the incoming connections will also be nonblocking since   */
    /* they will inherit that state from the listening socket.   */
    /*************************************************************/
    unsigned long iMode = 1;

    if (ioctl(server_fd, FIONBIO, (char *)&iMode) < 0)
    {
        perror("ioctl() failed");
        close(server_fd);
        exit(-1);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);



    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address))<0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }


    if (listen(server_fd, 3) < 0){
        perror("listen");
        exit(EXIT_FAILURE);
    }
    /*************************************************************/
    /* Initialize the master fd_set                              */
    /*************************************************************/
    FD_ZERO(&master_set);
    int max_sd = server_fd;
    FD_SET(server_fd, &master_set);
    /*************************************************************/
    /* Initialize the timeval struct to 3 minutes (3x60).  If no        */
    /* activity after 3 minutes this program will end.           */
    /*************************************************************/
    timeout.tv_sec  = 3 * 3;
    timeout.tv_usec = 0;
    //TODO make timeout for accept!
    while(running){
        /**********************************************************/
        /* Copy the master fd_set over to the working fd_set.     */
        /**********************************************************/
        memcpy(&working_set, &master_set, sizeof(master_set));
        /**********************************************************/
        /* Call select() and wait 3 minutes for it to complete.   */
        /**********************************************************/
        printf("Waiting on select()...\n");
        rc = select(max_sd + 1, &working_set, NULL, NULL, &timeout);
        /**********************************************************/
        /* Check to see if the select call failed.                */
        /**********************************************************/
        if (rc < 0)
        {
            perror("  select() failed");
            break;
        }
        /**********************************************************/
        /* Check to see if the 3 minute time out expired.         */
        /**********************************************************/
        if (rc == 0)
        {
            printf("  select() timed out.  End program.\n");
            break;
        }
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                                 (socklen_t*)&addrlen))<0){
            perror("accept error");
            exit(EXIT_FAILURE);
        }
        c->handleClient(new_socket, new_socket);
    }

    //close the socketFD
    close(server_fd);
    return 0;
}

void MySerialServer::stop() {
    running = false;
}
