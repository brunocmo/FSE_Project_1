#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>
#include <string.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <iostream>
#include <vector>

class Client {

    public:
        int sockfd;

        struct sockaddr_in servaddr;

        unsigned int sin_size;

        int connectResponse;

        char buffer[4];

        int numberReceived;

        Client(std::string address, int port);
        ~Client();

        bool sendToServer(int numberSender);

        bool recvFromServer();
};


#endif