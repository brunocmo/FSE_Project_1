#include <Server.hpp>

Server::Server(int port) {

     this->velocidadeMediaPrincipal = 0;
     this->velocidadeMediaAuxiliar = 0;

     this->carrosCima = 0;
     this->carrosEsquerda = 0;
     this->carrosBaixo = 0;
     this->carrosDireita = 0;
     this->quantidadeVermelho = 0;
     this->quantidadeVelocidade = 0;

    this->sinalEnviado = 0;

    // Criação de uma nova comunicação
    sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sockfd == -1)
    {
        perror("Falha na criacao do socket");
        exit(EXIT_FAILURE);
    }

    // Adicionar propriedades do servidor
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

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
            if(this->sinalEnviado != 0) {

                sendToClient(this->sinalEnviado);
            
            this->sinalEnviado = 0;

            } else {
                sendToClient(this->sinalEnviado);
            }


        }

        statusSemaphore(numeroCruzamento);
        usleep(1500);
    }

}

bool Server::sendToClient(int numberSender) {

    int n = send(connfd, &numberSender, sizeof(numberSender), MSG_CONFIRM);

    if( n == -1 ) {
        std::cout << "Erro ao enviar msg" << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;

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

void Server::printValues(Server * cruzamento, int numeroCruzamento) {

           std::cout << "==================== CRUZAMENTO " << numeroCruzamento << " =====================" << '\n';

            if(cruzamento->velocidadeMediaPrincipal != -1) {
            std::cout << "A velocidade média da via Principal é de " << cruzamento->velocidadeMediaPrincipal << " km/h" <<'\n';
            } else std::cout << "Sem veículos na via Principal" << '\n';

            if(cruzamento->velocidadeMediaAuxiliar != -1) {
            std::cout << "A velocidade média da via Auxiliar é de " << cruzamento->velocidadeMediaAuxiliar << " km/h" <<'\n';
            } else std::cout << "Sem veículos na via Auxiliar" << '\n';

            std::cout <<
                "Passaram " <<
                cruzamento->carrosCima <<
                " carros/min no sentido ↑" <<
            '\n';

            std::cout <<
                "Passaram " <<
                cruzamento->carrosEsquerda <<
                " carros/min no sentido ←" <<
            '\n';

            std::cout <<
                "Passaram " <<
                cruzamento->carrosBaixo <<
                " carros/min no sentido ↓" <<
            '\n';

            std::cout <<
                "Passaram " <<
                cruzamento->carrosDireita <<
                " carros/min no sentido →" <<
            '\n';

            std::cout << "Numero de infrações por sinal vermelho " <<
                      cruzamento->quantidadeVermelho <<
                      '\n';

            std::cout << "Numero de infrações por velocidade alta " <<
                      cruzamento->quantidadeVelocidade <<
                      '\n';

            std::cout << '\n';

}
