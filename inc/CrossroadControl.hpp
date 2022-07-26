#ifndef CROSSROADCONTROL_HPP
#define CROSSROADCONTROL_HPP

#include <cstdint>
#include <iostream>
#include <CrossroadSemaphore.hpp>

class CrossroadControl {

    public:
        std::uint8_t chronometer;
        bool interruptionOne;
        bool interruptionTwo;

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
            
        CrossroadControl();
        ~CrossroadControl();

        void controle();
        void changeState( std::uint8_t machineState );


};

#endif