#ifndef DISTRICTCONTROL_HPP
#define DISTRICTCONTROL_HPP

#include <CrossroadControl.hpp>
#include <signal.h>
#include <CleanValues.hpp>
#include <Client.hpp>

class DistrictControl {

    int counterSeconds;
    int twoSeconds;
    int sumVelocity;
    bool checkThisFirstCrossRoad;

    public:
        CrossroadControl * cruzamento;
        Client * clientSemaphore;

        DistrictControl( bool isThisFirstCrossRoad, std::string serverAddr, int portAddr );
        ~DistrictControl();

        void start();

        int carsPerMinute ( int numberOfCars ) ;

        void sendValuestoServer(int valueToSend);
        void receiveValuestoServer();

};


#endif