#include <Client.hpp>

Client::Client(std::string address, int port) {

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

    // Ativamente tenta estabelecer uma conexão
    sin_size = sizeof(struct sockaddr_in);

    connectResponse = connect(sockfd, (struct sockaddr *)&servaddr, sin_size);
    if(connectResponse == -1) {
        perror("Falha no connect!");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
}

Client::~Client() {
    close(sockfd);
}

bool Client::sendToServer(int numberSender) {

    int n = send(sockfd, &numberSender, sizeof(numberSender), MSG_CONFIRM);

    if( n == -1 ) {
        std::cout << "Erro ao enviar msg" << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;

}