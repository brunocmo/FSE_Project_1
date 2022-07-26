#include <iostream>
#include <unistd.h>
#include <CrossroadSemaphore.hpp>

int main() {

  CrossroadSemaphore semaforo1(true);
  
  std::cout << "Mandando mensagem" << '\n';
  semaforo1.sendMessage();

  sleep(5);

  std::cout << "Trocando valores mensagem" << '\n';
  semaforo1.changeValues();
  std::cout << "Mandando mensagem" << '\n';
  semaforo1.sendMessage();

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
