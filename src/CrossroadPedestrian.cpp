#include <CrossroadPedestrian.hpp>

bool checkThisFirstCrossRoadPedestrian = false;

bool interruptionPrincipal;
bool interruptionAuxiliar;

unsigned short int isPressed() {
  static struct timespec lastCall;
  struct timespec thisCall;
  float timeDiff;

  clock_gettime(CLOCK_REALTIME, &thisCall);
  timeDiff = (thisCall.tv_sec + thisCall.tv_nsec/1E9 - lastCall.tv_sec - lastCall.tv_nsec/1E9)*4;
  lastCall = thisCall;

  return timeDiff > 1 ? 1 : 0;
}

void buttonPrincipalActivation() {
    if (isPressed()) {
        interruptionPrincipal = true;
        std::cout << "Botão ativado 1 !" << '\n';
    }
}

void buttonAuxiliarActivation() {
    if (isPressed()) {
        interruptionAuxiliar = true;
        std::cout << "Botão ativado 2 !" << '\n';
    }

}

CrossroadPedestrian::CrossroadPedestrian( bool isThisFirstCrossRoad ) {

    checkThisFirstCrossRoadPedestrian = isThisFirstCrossRoad;

    wiringPiSetup();

    if(checkThisFirstCrossRoadPedestrian) {
        // Principal Sempahore
        pinMode(CRUZ_1_BUTTON_1, INPUT);
        pullUpDnControl(CRUZ_1_BUTTON_1, PUD_DOWN);
        // Auxiliar Semaphore
        pinMode(CRUZ_1_BUTTON_2, INPUT);
        pullUpDnControl(CRUZ_1_BUTTON_2, PUD_DOWN);

        wiringPiISR(CRUZ_1_BUTTON_1, INT_EDGE_RISING, buttonPrincipalActivation);
        wiringPiISR(CRUZ_1_BUTTON_2, INT_EDGE_RISING, buttonAuxiliarActivation);

    } else {
        // Principal Sempahore
        pinMode(CRUZ_2_BUTTON_1, INPUT);
        pullUpDnControl(CRUZ_2_BUTTON_1, PUD_DOWN);
        // Auxiliar Semaphore
        pinMode(CRUZ_2_BUTTON_2, INPUT); 
        pullUpDnControl(CRUZ_2_BUTTON_2, PUD_DOWN);

        wiringPiISR(CRUZ_2_BUTTON_1, INT_EDGE_RISING, buttonPrincipalActivation);
        wiringPiISR(CRUZ_2_BUTTON_2, INT_EDGE_RISING, buttonAuxiliarActivation);

    }

    interruptionPrincipal = false;
    interruptionAuxiliar = false;



}

CrossroadPedestrian::~CrossroadPedestrian() = default;

void CrossroadPedestrian::receiveMessage() {

    int button1{0};
    int button2{0};

    button1 = interruptionPrincipal;
    button2 = interruptionAuxiliar;


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