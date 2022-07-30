#ifndef CROSSROADPEDESTRIAN_HPP
#define CROSSROADPEDESTRIAN_HPP

    #include <iostream>
    #include <ButtonPedestrian.hpp>
    #include <wiringPi.h>
    #include <PinConstantsWiringPi.hpp>

    extern bool checkThisFirstCrossRoadPedestrian;

    extern bool interruptionPrincipal;
    extern bool interruptionAuxiliar;

    class CrossroadPedestrian {
        private:
            ButtonPedestrian buttonSemaphorePrincipal;
            ButtonPedestrian buttonSemaphoreAuxiliar;

        
        public:
            CrossroadPedestrian( bool isThisFirstCrossRoad );
            ~CrossroadPedestrian();

            void receiveMessage();

            void changeValueButtons(int button1 , int button2);

            bool getButtonPrincipal();
            bool getButtonAuxiliar();

            void clearValues();

    };

#endif