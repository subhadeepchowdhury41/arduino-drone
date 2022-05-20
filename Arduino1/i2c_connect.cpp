#include "i2c_connect.h"

I2C::I2C(Thrust* thrust) {
    this->thrust = thrust;
    Wire.begin(8);
}

void I2C::onReceive(int size) {
    if (size) {
        if (size == 9) {
            
        } else if (size == 8) {
            
        } else if (size == 4) {

        }
    }
}