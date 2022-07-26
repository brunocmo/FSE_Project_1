#include <CrossroadControl.hpp>

bool interruptionPrincipal = false;
bool interruptionAuxiliar = false;

unsigned short int isPressed(unsigned short int button) {
  static struct timespec lastCall;
  struct timespec thisCall;
  float timeDiff;

  clock_gettime(CLOCK_REALTIME, &thisCall);
  timeDiff = (thisCall.tv_sec + thisCall.tv_nsec/1E9 - lastCall.tv_sec - lastCall.tv_nsec/1E9)*2;
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


CrossroadControl::CrossroadControl() {
    this->chronometer = 0;
    interruptionPrincipal = false;
    interruptionAuxiliar = false;

    wiringPiISR(CRUZ_1_BUTTON_1, INT_EDGE_RISING, buttonPrincipalActivation);
    wiringPiISR(CRUZ_1_BUTTON_2, INT_EDGE_RISING, buttonAuxiliarActivation);
}

CrossroadControl::~CrossroadControl() {
    delete cruzamentoUm;
}

void CrossroadControl::controle() {
    switch(machineState) {
        case S1 :  
            if( chronometer != 9 ) chronometer++;
            else {
                changeState(S2);
            } break;
        case S2 :  
            if( chronometer != 9 && interruptionPrincipal != true ) chronometer++;
            else {
                cruzamentoUm->changeValuesPrincipal(false, true, false);
                cruzamentoUm->changeValuesAuxiliar(true, false, false);
                interruptionPrincipal = false;
                changeState(S3);
            } break;
        case S3 :  
            if( chronometer != 2 ) chronometer++;
            else {
                cruzamentoUm->changeValuesPrincipal(true, false, false);
                cruzamentoUm->changeValuesAuxiliar(false, false, true);
                changeState(S4);
            } break;
        case S4 :  
            if( chronometer != 4) chronometer++;
            else {
                changeState(S5);
            } break;
        case S5 :  
            if( chronometer != 4 && interruptionAuxiliar != true ) chronometer++;
            else {
                cruzamentoUm->changeValuesPrincipal(true, false, false);
                cruzamentoUm->changeValuesAuxiliar(false, true, false);
                interruptionAuxiliar = false;
                changeState(S6);
            } break;
        case S6 :  
            if( chronometer != 2 ) chronometer++;
            else {
                cruzamentoUm->changeValuesPrincipal(false, false, true);
                cruzamentoUm->changeValuesAuxiliar(true, false, false);
                changeState(S1);
            } break;
        default: 
            std::cout << "Strange reading, setting it to last FSM." << '\n';
            this->machineState = S6;
            this->chronometer = 3; break;
    }

    cruzamentoUm->sendMessage();
}

void CrossroadControl::changeState( std::uint8_t machineState ) {
    this->machineState = machineState;
    this->chronometer = 0;
}
