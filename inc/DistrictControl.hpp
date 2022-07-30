#ifndef DISTRICTCONTROL_HPP
#define DISTRICTCONTROL_HPP

#include <CrossroadControl.hpp>
#include <signal.h>
#include <CleanValues.hpp>

class DistrictControl {

    int counterSeconds;
    int twoSeconds;
    int sumVelocity;
    bool checkThisFirstCrossRoad;

    public:
        CrossroadControl * cruzamento;

        DistrictControl( bool isThisFirstCrossRoad );
        ~DistrictControl();

        void start();

        int carsPerMinute ( int numberOfCars ) ;

};


#endif