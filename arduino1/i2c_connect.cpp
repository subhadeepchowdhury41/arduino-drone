#include "i2c_connect.h"

I2C::I2C() {
    Wire.begin(8);
}