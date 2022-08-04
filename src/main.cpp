#include <DistrictControl.hpp>
#include <Server.hpp>
#include <thread>

Server * servidor1;
Server * servidor2;
Server * servidor3;
Server * servidor4;

int sairVisualizacao = 0;

void eraseServer(int sign) {
  delete servidor1;
  delete servidor2;
  delete servidor3;
  delete servidor4;
}

void sairVisu(int sign) {
  sairVisualizacao = 1;
}

int main(int argc, char *argv[]) {

  int escolhaMenu = 0;
  int escolheMenuDois = 0;

 if( argc != 3) {
    std::cout << "Erro, pass the right arguments!" << '\n';
    std::cout << "./prog <true|false>" << "\n";

    return 1;
  }

  DistrictControl * distrito;

  if( !(std::string(argv[1]).compare("server")) ) {
    signal(SIGINT, sairVisu);
    signal(SIGTERM, eraseServer);
    signal(SIGHUP, eraseServer);

    std::cout << "Ligando Clientes" << '\n';
    servidor1 = new Server(10041);
    std::cout << "Cliente 1, OK!" << '\n';
    servidor2 = new Server(10042);
    std::cout << "Cliente 2, OK!" << '\n';
    servidor3 = new Server(10043);
    std::cout << "Cliente 3, OK!" << '\n';
    servidor4 = new Server(10044);
    std::cout << "Cliente 4, OK!" << '\n';

    sleep(1);

    std::thread cruz1(&Server::receiveValues, servidor1, 1);
    std::thread cruz2(&Server::receiveValues, servidor2, 2);
    std::thread cruz3(&Server::receiveValues, servidor3, 3);
    std::thread cruz4(&Server::receiveValues, servidor4, 4);

    system("clear");

    while(true) {
      system("clear");
      std::cout << "Escolha um modo: " << '\n';
      std::cout << "1. Visualizar Cruzamentos" << '\n';
      std::cout << "2. Mudar Sinais Cruzamentos" << '\n';
      std::cout << "0. Sair" << '\n' << '\n';
      std::cout << "Selecionou: ";

      std::cin >> escolhaMenu;

      switch (escolhaMenu)
      {
        case 1:

          while(true) {
            sleep(1) ;
            system("clear");
            Server::printValues(servidor1, 1);
            Server::printValues(servidor2, 2);
            Server::printValues(servidor3, 3);
            Server::printValues(servidor4, 4);

            std::cout << "Pressione CTRL-C para sair! " << '\n';

            if(sairVisualizacao == 1) {
              sairVisualizacao = 0;
              break;
            }
          }

          break;
        
        case 2: 
          system("clear");
          std::cout << "Escolha um modo: " << '\n';
          std::cout << "1. Modo Noturno" << '\n';
          std::cout << "2. Modo Emergencia" << '\n';
          std::cout << "3. Modo Normal" << '\n';
          std::cout << "0. Voltar" << '\n' << '\n';
          std::cout << "Selecionou: ";

          std::cin >> escolheMenuDois;

          switch ( escolheMenuDois )
          {
            case 1:
              servidor1->sinalEnviado = 1;
              servidor2->sinalEnviado = 1;
              servidor3->sinalEnviado = 1;
              servidor4->sinalEnviado = 1;
              break;
            case 2:
              servidor1->sinalEnviado = 2;
              servidor2->sinalEnviado = 2;
              servidor3->sinalEnviado = 2;
              servidor4->sinalEnviado = 2;
              break;
            case 3:
              servidor1->sinalEnviado = 3;
              servidor2->sinalEnviado = 3;
              servidor3->sinalEnviado = 0;
              servidor4->sinalEnviado = 0;
              break;

            case 0: break;
            default:
              std::cout << "Escolha não reconhecida!" << '\n';
              servidor1->sinalEnviado = 0;
              servidor2->sinalEnviado = 0;
              servidor3->sinalEnviado = 0;
              servidor4->sinalEnviado = 0;
              break;
          }

          break;

        case 0 : 

          cruz1.detach();
          cruz2.detach();
          cruz3.detach();
          cruz4.detach();
          eraseServer(1); 
          return 0;
        
        default:
          std::cout << "Seleção de menu errado, tente novamente!" << '\n';
          break;
      }
    }


  } else {
    if ( !(std::string(argv[1]).compare("one"))) {
    distrito = new DistrictControl(true ,argv[2], 10041);
    } else if ( !(std::string(argv[1]).compare("two")) ) {
      distrito = new DistrictControl(false,argv[2], 10042);
    } else if ( !(std::string(argv[1]).compare("three")) ) {
      distrito = new DistrictControl(true,argv[2], 10043);
    } else if ( !(std::string(argv[1]).compare("four")) ) {
      distrito = new DistrictControl(false,argv[2], 10044);
    } else {

      std::cout << "Parametro de inicializaçao nao encontrado" << '\n';
      std::cout << "Usar: server, one, two, three, four" << '\n';
      std::cout << "Terminando o programa!" << '\n';
      return 0;
    }

    distrito->start();
  }

  return 0;
}
