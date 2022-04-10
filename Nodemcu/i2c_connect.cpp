#include "i2c_connect.h"

void I2C::I2C() {
    Wire.begin(D1, D2);
}