#include <CrossroadControl.hpp>

CrossroadControl::CrossroadControl() {
    this->chronometer = 0;
    this->machineState = 0;

}

CrossroadControl::~CrossroadControl() {
    delete cruzamentoUm;
    delete sensores;
    delete pedestres;
}

void CrossroadControl::controle() {
    switch(machineState) {
        case S1 :  
            if( chronometer != 9 ) chronometer++;
            else {
                changeState(S2);
            } break;
        case S2 :  
            if( chronometer != 9 && 
                !pedestres->getButtonAuxiliar() &&
                !sensores->getStopPassageLeft() &&
                !sensores->getStopPassageRight()             
              ) chronometer++;
            else {
                cruzamentoUm->changeValuesPrincipal(false, true, false);
                cruzamentoUm->changeValuesAuxiliar(true, false, false);
                pedestres->clearValues();
                sensores->cleanSensors();
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
            if( chronometer != 4 && 
                !pedestres->getButtonPrincipal() && 
                !sensores->getStopPassageUp() &&
                !sensores->getStopPassageDown()
                ) chronometer++;
            else {
                cruzamentoUm->changeValuesPrincipal(true, false, false);
                cruzamentoUm->changeValuesAuxiliar(false, true, false);
                pedestres->clearValues();
                sensores->cleanSensors();
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
