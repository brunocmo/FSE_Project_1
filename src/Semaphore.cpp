#include <Semaphore.hpp>

Semaphore::Semaphore() {
    this->red    = false;
    this->yellow = false;
    this->green  = false;
}

Semaphore::~Semaphore() = default;

bool Semaphore::getRed() {
    return this->red;
}

void Semaphore::setRed(bool red) {
    this->red = red;
}

bool Semaphore::getYellow() {
    return this->yellow;
}

void Semaphore::setYellow(bool yellow) {
    this->yellow = yellow;
}

bool Semaphore::getGreen() {
    return this->green;
}

void Semaphore::setGreen(bool green) {
    this->green = green;
}
