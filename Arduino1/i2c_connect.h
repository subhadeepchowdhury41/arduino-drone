#ifndef I2C_CONNECT_H
#define I2C_CONNECT_H

#include <Arduino.h>
#include <Wire.h>
#include "thrust.h"

class I2C {
    private:
        Thrust* thrust;
        void onRequest();
        void onReceive(int size);
    public:
        I2C(Thrust* thrust);
};

#endif