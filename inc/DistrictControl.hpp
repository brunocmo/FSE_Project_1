#ifndef DISTRICTCONTROL_HPP
#define DISTRICTCONTROL_HPP

#include <CrossroadControl.hpp>
#include <signal.h>
#include <CleanValues.hpp>

class DistrictControl {

    int counterSeconds{0};
    int twoSeconds{0};
    int sumVelocity{0};

    public:
        CrossroadControl cruzamento1;

        DistrictControl();
        ~DistrictControl();

        void start();

        int carsPerMinute ( int numberOfCars ) ;

};


#endif