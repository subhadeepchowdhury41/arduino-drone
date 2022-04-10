#ifndef I2C_CONNECT
#define I2C_CONNECT

#include <Arduino.h>

class I2C {
    private:
        
    public:
        I2C();
        void writeDataToAddress(char data[], int address);
        int readAddress();
        void writeAddress(int address, int writeAddress[], int size);
        int addressAvailable();
        void requestFrom(int addr, int size);
        
};

#endif