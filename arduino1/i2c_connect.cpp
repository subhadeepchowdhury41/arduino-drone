#include "i2c_connect.h"

I2C::I2C(Thrust* thrust) {
    this->thrust = thrust;
    Wire.begin(8);
}

void I2C::onReceive(int size) {
    if (size) {

    }
}