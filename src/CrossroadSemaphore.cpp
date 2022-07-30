#include <CrossroadSemaphore.hpp>

CrossroadSemaphore::CrossroadSemaphore( bool isThisFirstCrossRoad ) {
    semaphorePrincipal.setGreen(true);
    semaphoreAuxiliar.setRed(true);

    this->isThisFirstCrossRoad = isThisFirstCrossRoad;

    wiringPiSetup();

    if(isThisFirstCrossRoad) {
        // Auxiliar Semaphore
        pinMode(CRUZ_1_SEMAFORO_1_VERMELHO, OUTPUT);
        pinMode(CRUZ_1_SEMAFORO_1_AMARELO, OUTPUT);
        pinMode(CRUZ_1_SEMAFORO_1_VERDE, OUTPUT);
        // Principal Sempahore
        pinMode(CRUZ_1_SEMAFORO_2_VERMELHO, OUTPUT);
        pinMode(CRUZ_1_SEMAFORO_2_AMARELO, OUTPUT);
        pinMode(CRUZ_1_SEMAFORO_2_VERDE, OUTPUT);
    } else {
        // Auxiliar Semaphore
        pinMode(CRUZ_2_SEMAFORO_1_VERMELHO, OUTPUT);
        pinMode(CRUZ_2_SEMAFORO_1_AMARELO, OUTPUT);
        pinMode(CRUZ_2_SEMAFORO_1_VERDE, OUTPUT);
        // Principal Sempahore
        pinMode(CRUZ_2_SEMAFORO_2_VERMELHO, OUTPUT);
        pinMode(CRUZ_2_SEMAFORO_2_AMARELO, OUTPUT);
        pinMode(CRUZ_2_SEMAFORO_2_VERDE, OUTPUT);  
    }
}

CrossroadSemaphore::~CrossroadSemaphore() = default;

void CrossroadSemaphore::sendMessage() {

    if( isThisFirstCrossRoad ) {
        // Principal Sempahore
        digitalWrite(CRUZ_1_SEMAFORO_2_VERMELHO, semaphorePrincipal.getRed());
        digitalWrite(CRUZ_1_SEMAFORO_2_AMARELO, semaphorePrincipal.getYellow());
        digitalWrite(CRUZ_1_SEMAFORO_2_VERDE, semaphorePrincipal.getGreen());
        // Auxiliar Semaphore
        digitalWrite(CRUZ_1_SEMAFORO_1_VERMELHO, semaphoreAuxiliar.getRed());
        digitalWrite(CRUZ_1_SEMAFORO_1_AMARELO, semaphoreAuxiliar.getYellow());
        digitalWrite(CRUZ_1_SEMAFORO_1_VERDE, semaphoreAuxiliar.getGreen());
    } else {
        // Principal Sempahore
        digitalWrite(CRUZ_2_SEMAFORO_2_VERMELHO, semaphorePrincipal.getRed());
        digitalWrite(CRUZ_2_SEMAFORO_2_AMARELO, semaphorePrincipal.getYellow());
        digitalWrite(CRUZ_2_SEMAFORO_2_VERDE, semaphorePrincipal.getGreen());
        // Auxiliar Semaphore
        digitalWrite(CRUZ_2_SEMAFORO_1_VERMELHO, semaphoreAuxiliar.getRed());
        digitalWrite(CRUZ_2_SEMAFORO_1_AMARELO, semaphoreAuxiliar.getYellow());
        digitalWrite(CRUZ_2_SEMAFORO_1_VERDE, semaphoreAuxiliar.getGreen());        
    }
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