#include <CrossroadPedestrian.hpp>

bool interruptionPrincipal;
bool interruptionAuxiliar;

unsigned short int isPressed(unsigned short int button) {
  static struct timespec lastCall;
  struct timespec thisCall;
  float timeDiff;

  clock_gettime(CLOCK_REALTIME, &thisCall);
  timeDiff = (thisCall.tv_sec + thisCall.tv_nsec/1E9 - lastCall.tv_sec - lastCall.tv_nsec/1E9)*4;
  lastCall = thisCall;

  return timeDiff > 1 ? 1 : 0;
}

void buttonPrincipalActivation() {
    if (isPressed(CRUZ_1_BUTTON_1)) {
        interruptionPrincipal = true;
        std::cout << "Botão ativado 1 !" << '\n';
    }
}

void buttonAuxiliarActivation() {
    if (isPressed(CRUZ_1_BUTTON_2)) {
    interruptionAuxiliar = true;
    std::cout << "Botão ativado 2 !" << '\n';
}

}

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

    interruptionPrincipal = false;
    interruptionAuxiliar = false;

    wiringPiISR(CRUZ_1_BUTTON_1, INT_EDGE_RISING, buttonPrincipalActivation);
    wiringPiISR(CRUZ_1_BUTTON_2, INT_EDGE_RISING, buttonAuxiliarActivation);

}

CrossroadPedestrian::~CrossroadPedestrian() = default;

void CrossroadPedestrian::receiveMessage() {

    int button1{0};
    int button2{0};

    if(this->isThisFirstCrossRoad) {
        button1 = interruptionPrincipal;
        button2 = interruptionAuxiliar;

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

bool CrossroadPedestrian::getButtonPrincipal() {
    return buttonSemaphorePrincipal.getButtonPressed();
}

bool CrossroadPedestrian::getButtonAuxiliar() {
    return buttonSemaphoreAuxiliar.getButtonPressed();
}

void CrossroadPedestrian::clearValues(){
        this->buttonSemaphorePrincipal.setButtonPressed(false);
        interruptionPrincipal = false;


        this->buttonSemaphoreAuxiliar.setButtonPressed(false);
        interruptionAuxiliar = false;
}