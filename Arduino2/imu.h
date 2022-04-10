#ifndef IMU_H
#define IMU_H
#include <Arduino.h>
#include "pid.h"
#include <i2c_connect.h>

class IMU {
    private:

        // raw values
        int g_x, g_y, g_z;
        int a_x, a_y, a_z;

        // calculated values
        float curr_pitch;
        float curr_roll;
        float prev_pitch;
        float prev_roll;

        void setUpRegisters(I2C* i2c);
        void readMPUData(I2C* i2c);

    public:
        IMU();
        void calibrate();
        void calculateAngles();
        void findPID(PID* pid);
};

#endif