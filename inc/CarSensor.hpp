#ifndef CARSENSOR_HPP
#define CARSENSOR_HPP

class CarSensor {

    private:
        bool passageSensor;
        bool velocitySensorA;
        bool velocitySensorB;

    public:
        CarSensor();
        ~CarSensor();


        bool getPassageSensor();
        void setPassageSensor(bool passageSensor);

        bool getVelocitySensorA();
        void setVelocitySensorA(bool velocitySensorA);

        bool getVelocitySensorB();
        void setVelocitySensorB(bool velocitySensorB);

};

#endif