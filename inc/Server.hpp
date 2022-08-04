#ifndef SERVER_HPP
#define SERVER_HPP

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

class Server{

    public:

        int sockfd;

        int rc;
        int ls;
        int connfd;

        int receberValores[6] = {0};

        char buffer[256];

        struct sockaddr_in servaddr;
        struct sockaddr_in clientaddr;

        int velocidadeMediaPrincipal;
        int velocidadeMediaAuxiliar;

        int carrosCima;
        int carrosEsquerda;
        int carrosBaixo;
        int carrosDireita;
        int quantidadeVermelho;
        int quantidadeVelocidade;

        int sinalEnviado;

        unsigned int sin_size;

        Server(int port);
        ~Server();


        void receiveValues(int numeroCruzamento);

        void statusSemaphore(int numeroCruzamento);

        bool sendToClient(int numberSender);

        static void printValues(Server * cruzamento, int numeroCruzamento);

};


#endif