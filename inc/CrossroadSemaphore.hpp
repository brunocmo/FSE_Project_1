#ifndef CROSSROADSEMAPHORE_HPP
#define CROSSROADSEMAPHORE_HPP

#include <Semaphore.hpp>
#include <wiringPi.h>
#include <PinConstantsWiringPi.hpp>

class CrossroadSemaphore {

    // const int CRUZ_1_SEMAFORO_1_VERMELHO = 29;
    // const int CRUZ_1_SEMAFORO_1_AMARELO = 25;
    // const int CRUZ_1_SEMAFORO_1_VERDE = 31;

    // const int CRUZ_1_SEMAFORO_2_VERMELHO = 26;
    // const int CRUZ_1_SEMAFORO_2_AMARELO = 27;
    // const int CRUZ_1_SEMAFORO_2_VERDE = 28;


    // const int CRUZ_2_SEMAFORO_1_VERMELHO = 14;
    // const int CRUZ_2_SEMAFORO_1_AMARELO = 9;
    // const int CRUZ_2_SEMAFORO_1_VERDE = 8;

    // const int CRUZ_2_SEMAFORO_2_VERMELHO = 22;
    // const int CRUZ_2_SEMAFORO_2_AMARELO = 21;
    // const int CRUZ_2_SEMAFORO_2_VERDE = 30;


    private:
        Semaphore semaphorePrincipal;
        Semaphore semaphoreAuxiliar;
    
    public:
        CrossroadSemaphore( bool isThisFirstCrossRoad );
        ~CrossroadSemaphore();

        void sendMessage();
        void changeValuesPrincipal(bool red, bool yellow, bool green);
        void changeValuesAuxiliar(bool red, bool yellow, bool green);

};

#endif