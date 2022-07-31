#include <DistrictControl.hpp>
#include <Server.hpp>
#include <thread>

bool viaPrincipal = true;

Server * servidor1;
Server * servidor2;

void eraseServer(int sign) {
  delete servidor1;
  delete servidor2;
}

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

    std::thread cruz1(&Server::receiveValues, servidor1, 1);
    std::thread cruz2(&Server::receiveValues, servidor2, 2);

    pause();


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
