#include <CrossroadControl.hpp>

CrossroadControl::CrossroadControl( bool isThisFirstCrossRoad ) {
    this->chronometer = 0;
    this->machineState = 0;
    this->numberPassedRedPrincipal = 0;
    this->numberPassedRedAuxiliar = 0;
    this->numberPassedVelocityLimitPrincipal = 0;
    this->numberPassedVelocityLimitAuxiliar = 0;

    checkThisFirstCrossRoad = isThisFirstCrossRoad;

    cruzamento = new CrossroadSemaphore( checkThisFirstCrossRoad );
    sensores = new CrossroadSensors( checkThisFirstCrossRoad );
    pedestres = new CrossroadPedestrian( checkThisFirstCrossRoad );

}

CrossroadControl::~CrossroadControl() {
    delete cruzamento;
    delete sensores;
    delete pedestres;
}

void CrossroadControl::controle() {

    if ( passedUpVelocityPrincipal ) {
        passedPrincipalVelocityLimit();
        passedUpVelocityPrincipal = false;
    }

    if ( passedUpVelocityAuxiliar ) {
        passedAuxiliarVelocityLimit();
        passedUpVelocityAuxiliar = false;
    }

    switch(machineState) {
        case S1 :  
            if( chronometer != 9 ) chronometer++;
            else {
                changeState(S2);
            } break;
        case S2 :  
            if( chronometer != 9 && 
                !pedestres->getButtonAuxiliar() &&
                !sensores->getStopPassageUp() &&
                !sensores->getStopPassageDown()            
              ) chronometer++;
            else {
                cruzamento->changeValuesPrincipal(false, true, false);
                cruzamento->changeValuesAuxiliar(true, false, false);
                pedestres->clearValues();
                sensores->cleanSensors();
                changeState(S3);
            } break;
        case S3 :  
            if( chronometer != 2 ) chronometer++;
            else {
                cruzamento->changeValuesPrincipal(true, false, false);
                cruzamento->changeValuesAuxiliar(false, false, true);
                changeState(S4);
            } 
            if ( passedPrincipal ) {
                passedPrincipalRed();
                passedPrincipal = false;
            }

            if ( passedAuxiliar ) {
                passedAuxiliarRed();
                passedAuxiliar = false;
            }
            break;
        case S4 :  
            if( chronometer != 4) chronometer++;
            else {
                changeState(S5);
            } 
            if ( passedPrincipal ) {
                passedPrincipalRed();
                passedPrincipal = false;
            }

            if ( passedAuxiliar ) {
                passedAuxiliarRed();
                passedAuxiliar = false;
            }
            break;
        case S5 :  
            if( chronometer != 4 && 
                !pedestres->getButtonPrincipal() && 
                !sensores->getStopPassageLeft() &&
                !sensores->getStopPassageRight()
                ) chronometer++;
            else {
                cruzamento->changeValuesPrincipal(true, false, false);
                cruzamento->changeValuesAuxiliar(false, true, false);
                pedestres->clearValues();
                sensores->cleanSensors();
                changeState(S6);
            } 
            if ( passedPrincipal ) {
                passedPrincipalRed();
                passedPrincipal = false;
            }

            if ( passedAuxiliar ) {
                passedAuxiliarRed();
                passedAuxiliar = false;
            }

            break;
        case S6 :  
            if( chronometer != 2 ) chronometer++;
            else {
                cruzamento->changeValuesPrincipal(false, false, true);
                cruzamento->changeValuesAuxiliar(true, false, false);
                changeState(S1);
            } break;
        case S7 :
            if( chronometer != 1 ) chronometer++;
            else {
                cruzamento->changeValuesPrincipal(false, true, false);
                cruzamento->changeValuesAuxiliar(false, true, false);
                changeState(S8);
            } break;
        case S8 :
            if( chronometer != 1 ) chronometer++;
            else {
                cruzamento->changeValuesPrincipal(false, false, false);
                cruzamento->changeValuesAuxiliar(false, false, false);
                changeState(S7);
            } break;
        case S9 :
            if( chronometer != 1 ) chronometer++;
            else {
                cruzamento->changeValuesPrincipal(false, false, true);
                cruzamento->changeValuesAuxiliar(true, false, false);
                changeState(S9);
            } break;
        default: 
            std::cout << "Strange reading, setting it to last FSM." << '\n';
            this->machineState = S6;
            this->chronometer = 3; break;
    }

    cruzamento->sendMessage();
}

void CrossroadControl::changeState( std::uint8_t machineState ) {
    this->machineState = machineState;
    this->chronometer = 0;
}

bool CrossroadControl::passedPrincipalRed() {
    numberPassedRedPrincipal++;
}

bool CrossroadControl::passedAuxiliarRed() {
    numberPassedRedAuxiliar++;
}

bool CrossroadControl::passedPrincipalVelocityLimit() {
    numberPassedVelocityLimitPrincipal++;
}

bool CrossroadControl::passedAuxiliarVelocityLimit() {
    numberPassedVelocityLimitAuxiliar++;

}