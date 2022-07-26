#include <iostream>
#include <signal.h>

#include <wiringPi.h>

// #include <CrossroadSemaphore.hpp>
// #include <CrossroadSensors.hpp>
#include <CrossroadControl.hpp>

#include <CleanValues.hpp>

// void interrupcao(void) {
//   if(isPressed(15)) {
//     std::cout << "Interrompi hehehe" << '\n';
//   }
// }

int main() {
  signal(SIGINT, cleanUp);
  signal(SIGTERM, cleanUp);
  signal(SIGHUP, cleanUp);

  CrossroadControl controle;

  while(1) {
    controle.controle();
    sleep(1);
  }

  // CrossroadSensors teste(true);

  // pause();



  // wiringPiSetup();

  // pinMode(11, INPUT);
  // pullUpDnControl(11, PUD_DOWN);
  // pinMode(10, INPUT);
  // pullUpDnControl(10, PUD_DOWN);
  // // pinMode(10, INPUT);
  // // pinMode(11, INPUT);

  // // std::cout << "configurei" << '\n';

  // // sleep(1);

  // // std::cout << "O tempo passou" << '\n';
  // wiringPiISR(10, INT_EDGE_BOTH, &interrupcao);
  // wiringPiISR(11, INT_EDGE_BOTH, &interrupcao);

  // pause();

  // std::cout << "Passou o tempo uffa" << '\n';

  // std::cout << "Trocando valores mensagem" << '\n';
  // semaforo1.changeValues();
  // std::cout << "Mandando mensagem" << '\n';
  // semaforo1.sendMessage();

  // pinMode(10, INPUT);
  // pinMode(11, INPUT);


  // while(1) {
  // if( !(digitalRead(10)) ) std::cout << "Opa amigão, fui apertado 1" << '\n';
  // else std::cout << "Deu ruim 1 " << '\n';

  // if( !(digitalRead(11)) ) std::cout << "Opa amigão, fui apertado 2" << '\n';
  // else std::cout << "Deu ruim 2" << '\n';

  // sleep(1);
  // }

  return 0;

}
