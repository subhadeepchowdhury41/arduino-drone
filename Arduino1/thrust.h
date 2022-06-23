#ifndef THRUST_H
#define THRUST_H

#include <Arduino.h>

class Thrust {
    public:
        void setThrust(int t1, int t2, int t3, int t4);
        String getThrustString();
        Thrust();
        int t1;
        int t2;
        int t3;
        int t4;
};

#endif
