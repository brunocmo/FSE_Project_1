#ifndef CROSSROADSENSORS_HPP
#define CROSSROADSENSORS_HPP

#include <CarSensor.hpp>
#include <wiringPi.h>
#include <iostream>
#include <unistd.h>
#include <PinConstantsWiringPi.hpp>
#include <ctime>
#include <chrono>
#include <vector>
#include <thread>

void receiveSignalsVelocityPrincipalA();
void receiveSignalsVelocityPrincipalB();
void receiveSignalsVelocityAuxiliarA();
void receiveSignalsVelocityAuxiliarB();
int medianVelocity(
        std::chrono::_V2::system_clock::time_point B, 
        std::chrono::_V2::system_clock::time_point A 
    );

void receiveSignalsPassagePrincipal();
void receiveSignalsPassageAuxiliar();

extern std::vector<int> velocityVehiclesPrincipal;
extern std::vector<int> velocityVehiclesAuxiliar;

class CrossroadSensors {
    public:
        CarSensor sensorPrincipal;
        CarSensor sensorAuxiliar;

        bool isThisFirstCrossRoad;

        CrossroadSensors( bool isThisFirstCrossRoad );
        ~CrossroadSensors();
};

#endif