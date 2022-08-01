#include <Server.hpp>

Server::Server(std::string address, int port) {

    int velocidadeMediaPrincipal = 0;
    int velocidadeMediaAuxiliar = 0;

    int carrosCima = 0;
    int carrosEsquerda = 0;
    int carrosBaixo = 0;
    int carrosDireita = 0;
    int quantidadeVermelho = 0;
    int quantidadeVelocidade = 0;

    // Criação de uma nova comunicação
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1)
    {
        perror("Falha na criacao do socket");
        exit(EXIT_FAILURE);
    }

    // Adicionar propriedades do servidor
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(address.c_str());
    servaddr.sin_port = port;

    // Se liga com o endereço local do socket
    rc = bind(sockfd, (const struct sockaddr *)&servaddr, 
        sizeof(servaddr));

    if(rc == -1){
        perror("Falha no bind");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Anuncia para aceitar conexões
    ls = listen(sockfd, 5);
    if (ls == -1) {
        perror("Falha no listen!");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    sin_size = sizeof(struct sockaddr_in);

    connfd = accept(sockfd, (struct sockaddr *)&clientaddr, &sin_size);

}

Server::~Server() {

    close(sockfd);

}

void Server::receiveValues(int numeroCruzamento) {

    while(1) {
        // Block chamador até a requisição de conexão chega


        if( connfd == -1) {
            perror("Falha no accept!");
        } else {

            for(int i{0}; i<10; i++) {
                int valorRecebido = 0;

                int n = recv(connfd, &valorRecebido, sizeof(valorRecebido), MSG_CONFIRM);
                if( n == -1 ) {
                    std::cout << "Erro no recebimento da mensagem!" << '\n';
                } else receberValores[i] = valorRecebido;
            }
        }

        statusSemaphore(numeroCruzamento);
        usleep(500);
    }

}

void Server::statusSemaphore(int numeroCruzamento) {      
        this->velocidadeMediaPrincipal = receberValores[0];
        this->velocidadeMediaAuxiliar = receberValores[1];
        this->carrosCima = receberValores[2];
        this->carrosEsquerda = receberValores[3];
        this->carrosBaixo = receberValores[4];
        this->carrosDireita = receberValores[5];
        this->quantidadeVermelho = receberValores[6]+receberValores[7];
        this->quantidadeVelocidade = receberValores[8]+receberValores[9];

}
