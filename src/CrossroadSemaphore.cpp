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

void CrossroadSemaphore::changeValues() {
    semaphorePrincipal.setRed(true);
    semaphorePrincipal.setYellow(true);
    semaphorePrincipal.setGreen(false);

    semaphoreAuxiliar.setRed(false);
    semaphoreAuxiliar.setYellow(true);
    semaphoreAuxiliar.setGreen(true);
}