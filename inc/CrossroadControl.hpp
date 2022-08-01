#ifndef CROSSROADCONTROL_HPP
#define CROSSROADCONTROL_HPP

#include <cstdint>
#include <iostream>
#include <unistd.h>
#include <CrossroadSemaphore.hpp>
#include <CrossroadPedestrian.hpp>
#include <CrossroadSensors.hpp>


void buttonPrincipalActivation();
void buttonAuxiliarActivation();

class CrossroadControl {

    private:
        std::uint8_t chronometer;

        std::uint8_t machineState;

        enum {
            S1,
            S2,
            S3,
            S4,
            S5,
            S6
        };

        bool checkThisFirstCrossRoad;

    public:       

        CrossroadSemaphore * cruzamento;
        CrossroadSensors * sensores;
        CrossroadPedestrian * pedestres;

        int numberPassedRedPrincipal;
        int numberPassedRedAuxiliar;

        int numberPassedVelocityLimitPrincipal;
        int numberPassedVelocityLimitAuxiliar;

        CrossroadControl(  bool isThisFirstCrossRoad );
        ~CrossroadControl();

        void controle();
        void changeState( std::uint8_t machineState );

        bool passedPrincipalRed();
        bool passedAuxiliarRed();

        bool passedPrincipalVelocityLimit();
        bool passedAuxiliarVelocityLimit();
};

#endif