#ifndef CROSSROADCONTROL_HPP
#define CROSSROADCONTROL_HPP

#include <cstdint>
#include <iostream>
#include <unistd.h>
#include <CrossroadSemaphore.hpp>
#include <CrossroadPedestrian.hpp>
#include <CrossroadSensors.hpp>

extern bool interruptionPrincipal;
extern bool interruptionAuxiliar;

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

        CrossroadSemaphore * cruzamentoUm = new CrossroadSemaphore( true );
        CrossroadSensors * sensores = new CrossroadSensors( true );

    public:            
        CrossroadControl();
        ~CrossroadControl();

        void controle();
        void changeState( std::uint8_t machineState );


};

#endif