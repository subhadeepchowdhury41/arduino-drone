#ifndef I2C_CONNECT_H
#define I2C_CONNECT_H

#include <Arduino.h>
#include <Wire.h>

class I2C {
    private:
        void onRequest();
        void onReceive4();
    public:
        I2C();
};

#endif