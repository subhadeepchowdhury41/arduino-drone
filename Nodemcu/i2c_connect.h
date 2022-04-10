#ifndef I2C_CONNECT_H
#define I2C_CONNECT_H

#include <Arduino.h>

class I2C {
    public:
        I2C();
        void sendDataToArd1();
        void sendDataToArd2();
        void receiveThrust();
        void receiveAngle();
    private:
        int ard1_addr;
        int ard2_addr;
};


#endif