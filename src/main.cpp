#include <DistrictControl.hpp>

bool viaPrincipal = true;

int main(int argc, char *argv[]) {

  if( argc != 2) {
    std::cout << "Erro, pass the right arguments!" << '\n';
    std::cout << "./prog <true|false>" << "\n";

    return 1;
  }

  DistrictControl * distrito;

  if  ( !(std::string(argv[1]).compare("true"))) {
    distrito = new DistrictControl(true);
    viaPrincipal = true;
  } else {
    distrito = new DistrictControl(false);
    viaPrincipal = false;
  }

  distrito->start();

  return 0;
}
