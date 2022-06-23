#include "i2c_connect.h"
#include <Wire.h>

I2C::I2C(ContextData* context) {
    Wire.begin(D1, D2);
    this->context = context;
}

void I2C::receiveFromArd1() {
    Wire.requestFrom(8, 17);
    char buffer[17];
    int i = 0;
    while(Wire.available() > 0 && i < 17) {
      buffer[i] = Wire.read();
    }

//    Serial.println(buffer);

    context->setCurrThrusts(String(3000));
}
