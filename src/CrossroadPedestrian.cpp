#include <CrossroadPedestrian.hpp>

CrossroadPedestrian::CrossroadPedestrian( bool isThisFirstCrossRoad ) {

    this->isThisFirstCrossRoad = isThisFirstCrossRoad;

    wiringPiSetup();

    if(this->isThisFirstCrossRoad) {
        // Principal Sempahore
        pinMode(CRUZ_1_BUTTON_1, INPUT);
        // Auxiliar Semaphore
        pinMode(CRUZ_1_BUTTON_2, INPUT);
    } else {
        // Principal Sempahore
        pinMode(CRUZ_2_BUTTON_1, INPUT);
        // Auxiliar Semaphore
        pinMode(CRUZ_2_BUTTON_2, INPUT); 
    }

}

CrossroadPedestrian::~CrossroadPedestrian() = default;

void CrossroadPedestrian::receiveMessage() {

    int button1{0};
    int button2{0};

    if(this->isThisFirstCrossRoad) {
        button1 = digitalRead(CRUZ_1_BUTTON_1);
        button2 = digitalRead(CRUZ_1_BUTTON_2);

    } else {
        button1 = digitalRead(CRUZ_2_BUTTON_1);
        button2 = digitalRead(CRUZ_2_BUTTON_2);
    }
    changeValueButtons(button1, button2);
}

void CrossroadPedestrian::changeValueButtons(int button1, int button2) {
    this->buttonSemaphorePrincipal.setButtonPressed(button1);
    this->buttonSemaphoreAuxiliar.setButtonPressed(button2);
}

