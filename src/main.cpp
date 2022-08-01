#include <DistrictControl.hpp>
#include <Server.hpp>
#include <thread>

bool viaPrincipal = true;

Server * servidor1;
Server * servidor2;
// Server * servidor3;
// Server * servidor4;

void eraseServer(int sign) {
  delete servidor1;
  delete servidor2;
}

int cruzamento[4][10];

int main(int argc, char *argv[]) {


 if( argc != 2) {
    std::cout << "Erro, pass the right arguments!" << '\n';
    std::cout << "./prog <true|false>" << "\n";

    return 1;
  }

  DistrictControl * distrito;

  if( !(std::string(argv[1]).compare("server")) ) {
    signal(SIGINT, eraseServer);
    signal(SIGTERM, eraseServer);
    signal(SIGHUP, eraseServer);
    
    servidor1 = new Server("127.0.0.1", 10041);
    servidor2 = new Server("127.0.0.1", 10042);
    // servidor2 = new Server("127.0.0.1", 10043);
    // servidor2 = new Server("127.0.0.1", 10044);
    std::thread cruz1(&Server::receiveValues, servidor1, 1);
    std::thread cruz2(&Server::receiveValues, servidor2, 2);

    while(true) {

    }


  } else { 
    if  ( !(std::string(argv[1]).compare("true"))) {
    distrito = new DistrictControl(true ,"127.0.0.1", 10041);
    viaPrincipal = true;
    } else {
      distrito = new DistrictControl(false, "127.0.0.1", 10042);
      viaPrincipal = false;
    }

    distrito->start();
  }

  return 0;
}

void printValues(Server * cruzamento, int numeroCruzamento) {

           std::cout << "============ CRUZAMENTO " << numeroCruzamento << " =============" << '\n';

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