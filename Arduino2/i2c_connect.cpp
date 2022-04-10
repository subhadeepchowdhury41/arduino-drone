#include "i2c_connect.h"
#include <Wire.h>

void I2C::writeDataToAddress(char data[], int address) {
    Wire.beginTransmission(address);
    Wire.write(data);
    Wire.endTransmission();
}

void I2C::writeAddress(int address, int writeAddress[], int size) {
    Wire.beginTransmission(address);
    for (int i = 0; i < size; i++) {
        Wire.write(writeAddress[i]);
    }
    Wire.endTransmission();
}

int I2C::readAddress() {
    return Wire.read()<<8|Wire.read();
}

int I2C::addressAvailable() {
    return Wire.available();
}

void I2C::requestFrom(int addr, int size) {
    Wire.requestFrom(addr, size);
}

I2C::I2C() {
    Wire.begin(9);
}