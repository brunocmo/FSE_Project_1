#include <CrossroadSensors.hpp>

CrossroadSensors::CrossroadSensors(bool isThisFirstCrossRoad ) {
    wiringPiSetup();

    this->isThisFirstCrossRoad = isThisFirstCrossRoad;

    if( isThisFirstCrossRoad ) {
        pinMode(CRUZ_1_SENSOR_PASSAGEM_1, INPUT);
        pullUpDnControl(CRUZ_1_SENSOR_PASSAGEM_1, PUD_UP);
        pinMode(CRUZ_1_SENSOR_PASSAGEM_2, INPUT);
        pullUpDnControl(CRUZ_1_SENSOR_PASSAGEM_2, PUD_DOWN);
        pinMode(CRUZ_1_VELOCIDADE_1_A, INPUT);
        pullUpDnControl(CRUZ_1_VELOCIDADE_1_A, PUD_UP);
        pinMode(CRUZ_1_VELOCIDADE_1_B, INPUT);
        pullUpDnControl(CRUZ_1_VELOCIDADE_1_B, PUD_UP);
        pinMode(CRUZ_1_VELOCIDADE_2_A, INPUT);
        pullUpDnControl(CRUZ_1_VELOCIDADE_2_A, PUD_UP);
        pinMode(CRUZ_1_VELOCIDADE_2_B, INPUT);
        pullUpDnControl(CRUZ_1_VELOCIDADE_2_B, PUD_UP);


        wiringPiISR(CRUZ_1_VELOCIDADE_1_B, INT_EDGE_RISING, receiveSignalsVelocity);
        wiringPiISR(CRUZ_1_VELOCIDADE_2_B, INT_EDGE_RISING, receiveSignalsVelocity);
        wiringPiISR(CRUZ_1_SENSOR_PASSAGEM_1, INT_EDGE_RISING, receiveSignalsPassage);
        wiringPiISR(CRUZ_1_SENSOR_PASSAGEM_2, INT_EDGE_RISING, receiveSignalsPassage);

    } else {
        pinMode(CRUZ_2_SENSOR_PASSAGEM_1, INPUT);
        pullUpDnControl(CRUZ_2_SENSOR_PASSAGEM_1, PUD_DOWN);
        pinMode(CRUZ_2_SENSOR_PASSAGEM_2, INPUT);
        pullUpDnControl(CRUZ_2_SENSOR_PASSAGEM_2, PUD_DOWN);
        pinMode(CRUZ_2_VELOCIDADE_1_A, INPUT);
        pullUpDnControl(CRUZ_2_VELOCIDADE_1_A, PUD_DOWN);
        pinMode(CRUZ_2_VELOCIDADE_1_B, INPUT);
        pullUpDnControl(CRUZ_2_VELOCIDADE_1_B, PUD_DOWN);
        pinMode(CRUZ_2_VELOCIDADE_2_A, INPUT);
        pullUpDnControl(CRUZ_2_VELOCIDADE_2_A, PUD_DOWN);
        pinMode(CRUZ_2_VELOCIDADE_2_B, INPUT);
        pullUpDnControl(CRUZ_2_VELOCIDADE_2_B, PUD_DOWN);

        wiringPiISR(CRUZ_2_VELOCIDADE_1_B, INT_EDGE_RISING, receiveSignalsVelocity);
        wiringPiISR(CRUZ_2_VELOCIDADE_2_B, INT_EDGE_RISING, receiveSignalsVelocity);
        wiringPiISR(CRUZ_2_SENSOR_PASSAGEM_1, INT_EDGE_RISING, receiveSignalsPassage);
        wiringPiISR(CRUZ_2_SENSOR_PASSAGEM_2, INT_EDGE_RISING, receiveSignalsPassage);
    }

}

CrossroadSensors::~CrossroadSensors() = default;

void receiveSignalsVelocity() {

    auto t_start = std::chrono::high_resolution_clock::now();
    auto t_end = std::chrono::high_resolution_clock::now();

    bool isThisPrincipal = true;
    bool passou = false;
    
    if (isThisPrincipal) {
        std::cout << "Passou um carro na 1 " << '\n';

        for(int i{0}; i<50; i++) {
            
            if( digitalRead( CRUZ_1_VELOCIDADE_1_A ) ) {
                t_end = std::chrono::high_resolution_clock::now();
                std::cout << "Passou um carro na 2" << '\n';
                passou = true;
                break;
            } else {
            delay(50);
            }
        }


    }
    else {
        std::cout << "Passou um carro na 1 (auxiliar) " << '\n';

        for(int i{0}; i<50; i++) {
            if( digitalRead( CRUZ_2_VELOCIDADE_1_A ) ) {
                t_end = std::chrono::high_resolution_clock::now();
                std::cout << "Passou um carro na 2 (auxiliar)" << '\n';
                passou = true;
                break;
            }
            delay(50);
        }
    }


    if (!passou) {
        std::cout << "Veiculo não passou no segundo sensor!" << '\n';
    } else {
        double timeDiff = std::chrono::duration<double, std::milli>(t_end-t_start).count();
        std::cout << "A velocidade é de: " << ((1.0)/(timeDiff/1000.0)) * 3.6 << " km/h" << '\n';
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


