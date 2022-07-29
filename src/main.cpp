#include <iostream>
#include <signal.h>
#include <wiringPi.h>

#include <CrossroadControl.hpp>
#include <CleanValues.hpp>

int main() {
  signal(SIGINT, cleanUp);
  signal(SIGTERM, cleanUp);
  signal(SIGHUP, cleanUp);

  CrossroadControl controle;

  int twoSeconds{0};
  int sumVelocity{0};

  while(1) {

    controle.controle();
    sleep(1);

    if(twoSeconds > 1) {
      twoSeconds = -1;

      if(!velocityVehiclesPrincipal.empty()) {
      sumVelocity = 0;
      for( int veloc : velocityVehiclesPrincipal) sumVelocity+=veloc;
      sumVelocity/=int(velocityVehiclesPrincipal.size());
      std::cout << "A velocidade média da via Principal é de " << sumVelocity << " km/h" <<'\n';
      } else std::cout << "Sem veículos na via Principal" << '\n';

      if(!velocityVehiclesAuxiliar.empty()) {
      sumVelocity = 0;
      for( int veloc : velocityVehiclesAuxiliar) sumVelocity+=veloc;
      sumVelocity/=int(velocityVehiclesAuxiliar.size());
      
      std::cout << "A velocidade média da via Auxiliar é de " << sumVelocity << " km/h" <<'\n';
      } else std::cout << "Sem veículos na via Auxiliar" << '\n';
    }

    twoSeconds++;
  }
  
  return 0;

}
