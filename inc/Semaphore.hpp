#ifndef SEMAPHORE_HPP
#define SEMPAHORE_HPP

class Semaphore {

    private:
        bool red;
        bool yellow;
        bool green;
    
    public:
        Semaphore();
        ~Semaphore();

        bool getRed();
        void setRed(bool red);

        bool getYellow();
        void setYellow(bool yellow);

        bool getGreen();
        void setGreen(bool green);
};

#endif