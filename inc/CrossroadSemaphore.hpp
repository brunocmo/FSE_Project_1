#ifndef CROSSROADSEMAPHORE_HPP
#define CROSSROADSEMAPHORE_HPP

#include <Semaphore.hpp>
#include <wiringPi.h>
#include <PinConstantsWiringPi.hpp>

class CrossroadSemaphore {
    private:
        Semaphore semaphorePrincipal;
        Semaphore semaphoreAuxiliar;
    
    public:
        CrossroadSemaphore( bool isThisFirstCrossRoad );
        ~CrossroadSemaphore();

        void sendMessage();
        void changeValuesPrincipal(bool red, bool yellow, bool green);
        void changeValuesAuxiliar(bool red, bool yellow, bool green);
};

#endif