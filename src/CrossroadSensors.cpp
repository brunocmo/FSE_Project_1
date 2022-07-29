#include <CrossroadSensors.hpp>

std::vector<int> velocityVehiclesPrincipal;
std::vector<int> velocityVehiclesAuxiliar;

std::chrono::_V2::system_clock::time_point t_startPrincipal;
std::chrono::_V2::system_clock::time_point t_endPrincipal;
std::chrono::_V2::system_clock::time_point t_startAuxiliar;
std::chrono::_V2::system_clock::time_point t_endAuxiliar;

PI_THREAD (stoppedVehiculeInSemaphore) {
    
    for(int j{0}; j<2; j++) {
        sleep(1);
        if ( !digitalRead(CRUZ_1_VELOCIDADE_1_A) ) {
            std::cout << "Tem um carro parado aqui no VELO 1 A!" << '\n';
            break;
        }
    }

}

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


        wiringPiISR(CRUZ_1_VELOCIDADE_1_B, INT_EDGE_FALLING, receiveSignalsVelocityAuxiliarB);
        wiringPiISR(CRUZ_1_VELOCIDADE_1_A, INT_EDGE_FALLING, receiveSignalsVelocityAuxiliarA);
        
        wiringPiISR(CRUZ_1_VELOCIDADE_2_B, INT_EDGE_FALLING, receiveSignalsVelocityPrincipalB);
        wiringPiISR(CRUZ_1_VELOCIDADE_2_A, INT_EDGE_FALLING, receiveSignalsVelocityPrincipalA);

        wiringPiISR(CRUZ_1_SENSOR_PASSAGEM_1, INT_EDGE_FALLING, receiveSignalsPassageAuxiliar);
        wiringPiISR(CRUZ_1_SENSOR_PASSAGEM_2, INT_EDGE_FALLING, receiveSignalsPassagePrincipal);

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

        wiringPiISR(CRUZ_2_VELOCIDADE_1_B, INT_EDGE_FALLING, receiveSignalsVelocityAuxiliarB);
        wiringPiISR(CRUZ_2_VELOCIDADE_1_A, INT_EDGE_FALLING, receiveSignalsVelocityAuxiliarA);
        
        wiringPiISR(CRUZ_2_VELOCIDADE_2_B, INT_EDGE_FALLING, receiveSignalsVelocityPrincipalB);
        wiringPiISR(CRUZ_2_VELOCIDADE_2_A, INT_EDGE_FALLING, receiveSignalsVelocityPrincipalA);

        wiringPiISR(CRUZ_2_SENSOR_PASSAGEM_1, INT_EDGE_FALLING, receiveSignalsPassageAuxiliar);
        wiringPiISR(CRUZ_2_SENSOR_PASSAGEM_2, INT_EDGE_FALLING, receiveSignalsPassagePrincipal);
    }

}

CrossroadSensors::~CrossroadSensors() = default;

// void receiveSignalsVelocity() {

//     auto t_start = std::chrono::high_resolution_clock::now();
//     auto t_end = std::chrono::high_resolution_clock::now();

//     bool isThisPrincipal = true;
//     bool passou = false;
    
//     if (isThisPrincipal) {
//         std::cout << "Passou um carro na 1 " << '\n';

//         for(int i{0}; i<150; i++) {
//             std::cout << "debug " << !(digitalRead( CRUZ_1_VELOCIDADE_1_A )) << '\n';
            
//             if( !(digitalRead( CRUZ_1_VELOCIDADE_1_A )) ) {
//                 t_end = std::chrono::high_resolution_clock::now();
//                 std::cout << "Passou um carro na 2" << '\n';
//                 passou = true;
//                 break;
//             }
//             delay(20);
//         }


//     }
//     else {
//         std::cout << "Passou um carro na 1 (auxiliar) " << '\n';

//         for(int i{0}; i<50; i++) {
//             if( digitalRead( !CRUZ_2_VELOCIDADE_1_A ) ) {
//                 t_end = std::chrono::high_resolution_clock::now();
//                 std::cout << "Passou um carro na 2 (auxiliar)" << '\n';
//                 passou = true;
//                 break;
//             }
//             delay(50);
//         }
//     }


//     if (!passou) {
//         std::cout << "Veiculo não passou no segundo sensor!" << '\n';
//     } else {
//         double timeDiff = std::chrono::duration<double, std::milli>(t_end-t_start).count();
//         std::cout << "A velocidade é de: " << ((1.0)/(timeDiff/1000.0)) * 3.6 << " km/h" << '\n';
//     }

// }

void receiveSignalsVelocityPrincipalB() {
    t_startPrincipal = std::chrono::high_resolution_clock::now();
}

void receiveSignalsVelocityPrincipalA() {
    t_endPrincipal = std::chrono::high_resolution_clock::now();
    double timeDiff = medianVelocity(t_startPrincipal, t_endPrincipal);
    timeDiff = ((1.0)/(timeDiff/1000.0)) * 3.6;
    velocityVehiclesAuxiliar.push_back(int(timeDiff));
    std::cout << "A velocidade é de: " << int(timeDiff) << " km/h" << '\n';

}

void receiveSignalsVelocityAuxiliarB() {
    t_startAuxiliar = std::chrono::high_resolution_clock::now();

}

void receiveSignalsVelocityAuxiliarA() {
    t_endAuxiliar = std::chrono::high_resolution_clock::now();
    double timeDiff = medianVelocity(t_startAuxiliar, t_endAuxiliar);
    timeDiff = ((1.0)/(timeDiff/1000.0)) * 3.6;
    velocityVehiclesAuxiliar.push_back(int(timeDiff));
    std::cout << "A velocidade é de: " << int(timeDiff) << " km/h" << '\n';

    int result = piThreadCreate( stoppedVehiculeInSemaphore );

    if (result != 0)
        std::cout << "Broken" << '\n';
}

int medianVelocity(
        std::chrono::_V2::system_clock::time_point B, 
        std::chrono::_V2::system_clock::time_point A 
    ) {
    return double(std::chrono::duration<double, std::milli>(A-B).count());
}

void receiveSignalsPassagePrincipal() {
    std::cout << "Tem alquem parado aqui na Principal! " << '\n';
}

void receiveSignalsPassageAuxiliar() {
    std::cout << "Aqui na auxiliar, Carro parado" << '\n';
}


