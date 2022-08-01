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


extern bool checkThisFirstCrossRoad;

extern std::vector<int> velocityVehiclesPrincipal;
extern std::vector<int> velocityVehiclesAuxiliar;
extern int numberPassedCarsUp;
extern int numberPassedCarsDown;

extern bool upStopSensor;
extern bool downStopSensor;

extern bool leftStopSensor;
extern bool rightStopSensor;

extern bool passedPrincipal;
extern bool passedAuxiliar;
extern bool passedUp;
extern bool passedDown;

extern bool passedUpVelocityPrincipal;
extern bool passedUpVelocityAuxiliar;

class CrossroadSensors {

    CarSensor sensorPrincipal;
    CarSensor sensorAuxiliar;


    public:
        CrossroadSensors( bool isThisFirstCrossRoad );
        ~CrossroadSensors();

        void receiveSensors();
        void cleanSensors();

        bool getStopPassageUp();
        bool getStopPassageLeft();
        bool getStopPassageRight();
        bool getStopPassageDown();

        int getCarsNumberPassageUp();
        int getCarsNumberPassageLeft();
        int getCarsNumberPassageRight();
        int getCarsNumberPassageDown();


};

#endif