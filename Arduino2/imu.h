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

        float normalizer;
        float rad_conv;
        float acc_vec;

        float acc_pitch;
        float acc_roll;

        // calculated values
        float curr_pitch;
        float curr_roll;

        float curr_pitch_out;
        float curr_roll_out;

        float prev_pitch;
        float prev_roll;

        bool set_gyro_angle;
        
        void setUpRegisters(I2C* i2c);
        void readMPUData(I2C* i2c);

    public:
        IMU();
        void calibrate();
        void calculateAngles();
        void findPID(PID* pid);
};

#endif