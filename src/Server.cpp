#include <Server.hpp>

Server::Server(std::string address, int port) {
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

            for(int i{0}; i<6; i++) {
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
            std::cout << "============ CRUZAMENTO " << numeroCruzamento << " =============" << '\n';

            if(receberValores[0] != -1) {
            std::cout << "A velocidade média da via Principal é de " << receberValores[0] << " km/h" <<'\n';
            } else std::cout << "Sem veículos na via Principal" << '\n';

            if(receberValores[1] != -1) {          
            std::cout << "A velocidade média da via Auxiliar é de " << receberValores[1] << " km/h" <<'\n';
            } else std::cout << "Sem veículos na via Auxiliar" << '\n';

            std::cout << 
                "Passaram " << 
                receberValores[2] <<
                " carros/min no sentido ↑" << 
            '\n';

            std::cout << 
                "Passaram " << 
                receberValores[3] <<
                " carros/min no sentido ←" << 
            '\n';

            std::cout << 
                "Passaram " << 
                receberValores[4] <<
                " carros/min no sentido ↓" << 
            '\n';

            std::cout << 
                "Passaram " << 
                receberValores[5] <<
                " carros/min no sentido →" << 
            '\n';

            std::cout << '\n';
}
