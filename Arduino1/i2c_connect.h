#ifndef I2C_CONNECT_H
#define I2C_CONNECT_H

#include <Arduino.h>
#include <Wire.h>
#include "thrust.h"

class I2C {
    public:
        I2C(Thrust* thrust);
};

#endif
