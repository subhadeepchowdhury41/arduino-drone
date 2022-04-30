#include "imu.h"
#include "i2c_connect.h"


IMU::IMU() {
    int freq = 20;
    set_gyro_angle = false;
    normalizer = 1 / (freq * 65.5);
    rad_conv = normalizer * 3.142 / 180;
}

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

void IMU::calculateAngles() {

    curr_pitch = g_x * normalizer;
    curr_roll = g_y * normalizer;

    curr_pitch += curr_roll * sin(g_z * rad_conv);
    curr_roll -= curr_pitch * sin(g_z * rad_conv);

    acc_vec = sqrt((a_x*a_x) + (a_y* a_y) + (a_z*a_z));

    acc_pitch = asin((float) a_y / acc_vec) * 180 / 3.142;
    acc_roll = asin((float) a_y / acc_vec) * -180 / 3.142;

    acc_pitch -= acc_pitch_cal;
    acc_roll -= acc_roll_cal;

    if (!set_gyro_angle) {
        curr_pitch = acc_pitch;
        curr_roll = acc_roll;
        set_gyro_angle = true;
    } else {
        curr_pitch = curr_pitch * 0.96 + acc_pitch * 0.04;
        curr_roll = curr_roll * 0.96 + acc_roll * 0.04;
    }

    curr_pitch_out = curr_pitch_out * 0.9 + curr_pitch * 0.1;
    curr_roll_out = curr_roll_out * 0.9 + curr_roll * 0.1;

}

