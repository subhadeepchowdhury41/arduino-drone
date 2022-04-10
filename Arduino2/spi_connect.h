#ifndef SPI_CONNECT_H
#define SPI_CONNECT_H

#include <Arduino.h>
#include <SPI.h>

class SPIMaster {
    public:
        void sendPID(PID* pid);
        SPIMaster();
};

#endif
