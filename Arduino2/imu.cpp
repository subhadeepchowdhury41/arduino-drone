#include "imu.h"
#include "i2c_connect.h"

void IMU::readMPUData(I2C* i2c) {
    int addr[] = {0x3B};
    i2c->writeAddress(0x68, addr, 1);

    i2c->requestFrom(0X68, 14);

    while(i2c->addressAvailable() < 14);

    a_x = i2c->readAddress();
    a_y = i2c->readAddress();
    a_z = i2c->readAddress();

    int temp = i2c->readAddress();

    g_x = i2c->readAddress();
    g_y = i2c->readAddress();
    g_z = i2c->readAddress();
}