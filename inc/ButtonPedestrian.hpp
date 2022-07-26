#ifndef BUTTONPEDESTRIAN_HPP
#define BUTTONPEDESTRIAN_HPP

class ButtonPedestrian {

    private:
    bool buttonPressed;
    
    public:
        ButtonPedestrian();
        ~ButtonPedestrian();

        bool getButtonPressed();
        void setButtonPressed(bool buttonPressed);

};


#endif