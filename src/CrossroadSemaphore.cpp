#include <CrossroadSemaphore.hpp>

CrossroadSemaphore::CrossroadSemaphore( bool isThisFirstCrossRoad ) {
    semaphorePrincipal.setGreen(true);
    semaphoreAuxiliar.setRed(true);


    wiringPiSetup();

    if(isThisFirstCrossRoad) {
        // Principal Sempahore
        pinMode(CRUZ_1_SEMAFORO_1_VERMELHO, OUTPUT);
        pinMode(CRUZ_1_SEMAFORO_1_AMARELO, OUTPUT);
        pinMode(CRUZ_1_SEMAFORO_1_VERDE, OUTPUT);
        // Auxiliar Semaphore
        pinMode(CRUZ_1_SEMAFORO_2_VERMELHO, OUTPUT);
        pinMode(CRUZ_1_SEMAFORO_2_AMARELO, OUTPUT);
        pinMode(CRUZ_1_SEMAFORO_2_VERDE, OUTPUT);
    } else {
        // Principal Sempahore
        pinMode(CRUZ_2_SEMAFORO_1_VERMELHO, OUTPUT);
        pinMode(CRUZ_2_SEMAFORO_1_AMARELO, OUTPUT);
        pinMode(CRUZ_2_SEMAFORO_1_VERDE, OUTPUT);
        // Auxiliar Semaphore
        pinMode(CRUZ_2_SEMAFORO_2_VERMELHO, OUTPUT);
        pinMode(CRUZ_2_SEMAFORO_2_AMARELO, OUTPUT);
        pinMode(CRUZ_2_SEMAFORO_2_VERDE, OUTPUT);  
    }

}

CrossroadSemaphore::~CrossroadSemaphore() = default;

void CrossroadSemaphore::sendMessage() {
    // Principal Sempahore
    digitalWrite(CRUZ_1_SEMAFORO_1_VERMELHO, semaphorePrincipal.getRed());
    digitalWrite(CRUZ_1_SEMAFORO_1_AMARELO, semaphorePrincipal.getYellow());
    digitalWrite(CRUZ_1_SEMAFORO_1_VERDE, semaphorePrincipal.getGreen());
    // Auxiliar Semaphore
    digitalWrite(CRUZ_1_SEMAFORO_2_VERMELHO, semaphoreAuxiliar.getRed());
    digitalWrite(CRUZ_1_SEMAFORO_2_AMARELO, semaphoreAuxiliar.getYellow());
    digitalWrite(CRUZ_1_SEMAFORO_2_VERDE, semaphoreAuxiliar.getGreen());
}

void CrossroadSemaphore::changeValuesPrincipal(bool red, bool yellow, bool green) {
    semaphorePrincipal.setRed(red);
    semaphorePrincipal.setYellow(yellow);
    semaphorePrincipal.setGreen(green);
}


void CrossroadSemaphore::changeValuesAuxiliar(bool red, bool yellow, bool green) {
    semaphoreAuxiliar.setRed(red);
    semaphoreAuxiliar.setYellow(yellow);
    semaphoreAuxiliar.setGreen(green);
}