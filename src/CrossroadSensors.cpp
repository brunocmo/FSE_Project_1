#include <CrossroadSensors.hpp>

CrossroadSensors::CrossroadSensors(bool isThisFirstCrossRoad ) {
    wiringPiSetup();

    this->isThisFirstCrossRoad = isThisFirstCrossRoad;

    if( isThisFirstCrossRoad ) {
        pinMode(CRUZ_1_SENSOR_PASSAGEM_1, INPUT);
        pullUpDnControl(CRUZ_1_SENSOR_PASSAGEM_1, PUD_UP);
        pinMode(CRUZ_1_SENSOR_PASSAGEM_2, INPUT);
        pullUpDnControl(CRUZ_1_SENSOR_PASSAGEM_2, PUD_UP);
        pinMode(CRUZ_1_VELOCIDADE_1_A, INPUT);
        pullUpDnControl(CRUZ_1_VELOCIDADE_1_A, PUD_UP);
        pinMode(CRUZ_1_VELOCIDADE_1_B, INPUT);
        pullUpDnControl(CRUZ_1_VELOCIDADE_1_B, PUD_UP);
        pinMode(CRUZ_1_VELOCIDADE_2_A, INPUT);
        pullUpDnControl(CRUZ_1_VELOCIDADE_2_A, PUD_UP);
        pinMode(CRUZ_1_VELOCIDADE_2_B, INPUT);
        pullUpDnControl(CRUZ_1_VELOCIDADE_2_B, PUD_UP);
    } else {
        pinMode(CRUZ_2_SENSOR_PASSAGEM_1, INPUT);
        pullUpDnControl(CRUZ_2_SENSOR_PASSAGEM_1, PUD_UP);
        pinMode(CRUZ_2_SENSOR_PASSAGEM_2, INPUT);
        pullUpDnControl(CRUZ_2_SENSOR_PASSAGEM_2, PUD_UP);
        pinMode(CRUZ_2_VELOCIDADE_1_A, INPUT);
        pullUpDnControl(CRUZ_2_VELOCIDADE_1_A, PUD_UP);
        pinMode(CRUZ_2_VELOCIDADE_1_B, INPUT);
        pullUpDnControl(CRUZ_2_VELOCIDADE_1_B, PUD_UP);
        pinMode(CRUZ_2_VELOCIDADE_2_A, INPUT);
        pullUpDnControl(CRUZ_2_VELOCIDADE_2_A, PUD_UP);
        pinMode(CRUZ_2_VELOCIDADE_2_B, INPUT);
        pullUpDnControl(CRUZ_2_VELOCIDADE_2_B, PUD_UP);
    }

    wiringPiISR(CRUZ_1_VELOCIDADE_1_A, INT_EDGE_BOTH, receiveSignalsVelocity);
    wiringPiISR(CRUZ_1_SENSOR_PASSAGEM_1, INT_EDGE_BOTH, receiveSignalsPassage);
}

CrossroadSensors::~CrossroadSensors() = default;

void receiveSignalsVelocity() {

    bool isThisPrincipal = true;

    if (isThisPrincipal) {
        std::cout << "Passou um carro na 1 " << '\n';

        while(1) {
            if( !digitalRead( CRUZ_1_VELOCIDADE_1_B ) ) {
                std::cout << "Passou um carro na 2" << '\n';
                break;
            } else {
            delay(50);
            }
        }
    }
    else {
        std::cout << "Passou um carro na 1 (auxiliar) " << '\n';

        while(1) {
            if( !digitalRead( CRUZ_2_VELOCIDADE_1_B ) ) {
                std::cout << "Passou um carro na 2 (auxiliar)" << '\n';
                break;
            }
            delay(50);
        }
    }
}

void receiveSignalsPassage() {

    bool isThisPrincipal = true;

    if (isThisPrincipal)
    std::cout << "Tem alquem parado aqui na Principal! " << '\n';
    else
    std::cout << "Aqui na auxiliar, Carro parado" << '\n';

}

// void receiveSignalsPassage() {

//     bool isThisPrincipal = true;

//     if (isThisPrincipal)
//     std::cout << "Tem alquem parado aqui na Principal! " << '\n';
//     else
//     std::cout << "Aqui na auxiliar, Carro parado" << '\n';

// }


