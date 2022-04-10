#ifndef PID_H
#define PID_H

class PID {
    private:
        int pid1;
        int pid2;
    public:
        void calculatePID(IMU imu, int p_t, int c_t);
};

#endif