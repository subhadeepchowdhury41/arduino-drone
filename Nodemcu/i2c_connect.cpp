#include "i2c_connect.h"
#include <Wire.h>

I2C::I2C() {
    Wire.begin(D1, D2);
}

void I2C::receiveAngle() {
  
}
