#ifndef CROSSROADSENSORS_HPP
#define CROSSROADSENSORS_HPP

#include <CarSensor.hpp>
#include <wiringPi.h>
#include <iostream>
#include <unistd.h>
#include <PinConstantsWiringPi.hpp>

void receiveSignalsVelocity();
void receiveSignalsPassage();

class CrossroadSensors {
    public:
        CarSensor sensorPrincipal;
        CarSensor sensorAuxiliar;

        bool isThisFirstCrossRoad;

        CrossroadSensors( bool isThisFirstCrossRoad );
        ~CrossroadSensors();

        // void receiveSignalsPassage();
        // void receiveSignalsVelocity();
};

#endif