#include <ButtonPedestrian.hpp>

ButtonPedestrian::ButtonPedestrian() {
    this->buttonPressed = false;
}

ButtonPedestrian::~ButtonPedestrian() = default;

bool ButtonPedestrian::getButtonPressed() {
    return this->buttonPressed;
}

void ButtonPedestrian::setButtonPressed(bool buttonPressed) {
    this->buttonPressed = buttonPressed;
}