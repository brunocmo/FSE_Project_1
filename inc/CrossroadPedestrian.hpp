#ifndef CROSSROADPEDESTRIAN_HPP
#define CROSSROADPEDESTRIAN_HPP

    #include <iostream>
    #include <ButtonPedestrian.hpp>
    #include <wiringPi.h>
    #include <PinConstantsWiringPi.hpp>

    class CrossroadPedestrian {


        // const int CRUZ_1_BUTTON_1 = 10;
        // const int CRUZ_1_BUTTON_2 = 11;

        // const int CRUZ_2_BUTTON_1 = 12;
        // const int CRUZ_2_BUTTON_2 = 13;


        private:
            ButtonPedestrian buttonSemaphorePrincipal;
            ButtonPedestrian buttonSemaphoreAuxiliar;

            bool isThisFirstCrossRoad;
        
        public:
            CrossroadPedestrian( bool isThisFirstCrossRoad );
            ~CrossroadPedestrian();

            void receiveMessage();

            void changeValueButtons(int button1 , int button2);

    };

#endif