#include <CrossroadSensors.hpp>

std::vector<int> velocityVehiclesPrincipal;
std::vector<int> velocityVehiclesAuxiliar;

std::chrono::_V2::system_clock::time_point t_startPrincipal;
std::chrono::_V2::system_clock::time_point t_endPrincipal;
std::chrono::_V2::system_clock::time_point t_startAuxiliar;
std::chrono::_V2::system_clock::time_point t_endAuxiliar;

bool upSensor = false;
bool downSensor = false;
bool leftStopSensor = false;
bool rightStopSensor = false;

int numberPassedCarsUp = 0;
int numberPassedCarsDown = 0;

PI_THREAD (stoppedLeftVehiculeInSemaphore) {
    
    for(int j{0}; j<2; j++) {
        sleep(1);
        if ( !digitalRead(CRUZ_1_VELOCIDADE_1_A) ) {
            std::cout << "Tem um carro parado aqui no VELO 1 A!" << '\n';
            leftStopSensor = true;
            break;
        }
    }

}

PI_THREAD (stoppedRightVehiculeInSemaphore) {
    
    for(int j{0}; j<2; j++) {
        sleep(1);
        if ( !digitalRead(CRUZ_1_VELOCIDADE_2_A) ) {
            std::cout << "Tem um carro parado aqui no VELO 2 A!" << '\n';
            rightStopSensor = true;
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


void CrossroadSensors::receiveSensors() {
    sensorPrincipal.setPassageSensor(upSensor);
    sensorAuxiliar.setPassageSensor(downSensor);
    sensorPrincipal.setVelocitySensorA(leftStopSensor);
    sensorAuxiliar.setVelocitySensorA(rightStopSensor);
}

void CrossroadSensors::cleanSensors() {
    sensorPrincipal.setPassageSensor(false);
    sensorAuxiliar.setPassageSensor(false);
    sensorPrincipal.setVelocitySensorB(false);
    sensorAuxiliar.setVelocitySensorB(false);

    upSensor = false;
    downSensor = false;
    leftStopSensor = false;
    rightStopSensor = false;

}

bool CrossroadSensors::getStopPassageUp() {
    return sensorPrincipal.getPassageSensor();
}

bool CrossroadSensors::getStopPassageDown() {
    return sensorAuxiliar.getPassageSensor();
}

bool CrossroadSensors::getStopPassageLeft() {
    return sensorPrincipal.getVelocitySensorA();
}

bool CrossroadSensors::getStopPassageRight() {
    return sensorAuxiliar.getVelocitySensorA();
}

int CrossroadSensors::getCarsNumberPassageUp() {
    return numberPassedCarsUp;
}

int CrossroadSensors::getCarsNumberPassageLeft() {
    return int(velocityVehiclesPrincipal.size());
}

int CrossroadSensors::getCarsNumberPassageRight() {
    return int(velocityVehiclesAuxiliar.size());
}

int CrossroadSensors::getCarsNumberPassageDown() {
    return numberPassedCarsDown;
}

void receiveSignalsVelocityPrincipalB() {
    t_startPrincipal = std::chrono::high_resolution_clock::now();
}

void receiveSignalsVelocityPrincipalA() {
    t_endPrincipal = std::chrono::high_resolution_clock::now();
    double timeDiff = medianVelocity(t_startPrincipal, t_endPrincipal);
    timeDiff = ((1.0)/(timeDiff/1000.0)) * 3.6;
    velocityVehiclesPrincipal.push_back(int(timeDiff));
    std::cout << "A velocidade é de: " << int(timeDiff) << " km/h" << '\n';

    int result = piThreadCreate( stoppedRightVehiculeInSemaphore );

    if (result != 0)
        std::cout << "Broken" << '\n';

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

    int result = piThreadCreate( stoppedLeftVehiculeInSemaphore );

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
    std::cout << "Tem alquem parado aqui em Cima! " << '\n';
    upSensor = true;
    numberPassedCarsUp++;
    
}

void receiveSignalsPassageAuxiliar() {
    std::cout << "Aqui em baixo, Carro parado" << '\n';
    downSensor = true;
    numberPassedCarsDown++;
}



