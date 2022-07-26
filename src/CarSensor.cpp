#include <CarSensor.hpp>

CarSensor::CarSensor() {
    this->passageSensor = false;
    this->velocitySensorA = false;
    this->velocitySensorB = false;
}

CarSensor::~CarSensor() = default;

bool CarSensor::getPassageSensor() {
    return this->passageSensor; 
}

void CarSensor::setPassageSensor(bool passageSensor) {
    this->passageSensor = passageSensor;
}

bool CarSensor::getVelocitySensorA() {
    return this->velocitySensorA; 
}

void CarSensor::setVelocitySensorA(bool velocitySensorA) {
    this->velocitySensorA = velocitySensorA;
}

bool CarSensor::getVelocitySensorB() {
    return this->velocitySensorB; 
}

void CarSensor::setVelocitySensorB(bool velocitySensorB) {
    this->velocitySensorB = velocitySensorB;
}