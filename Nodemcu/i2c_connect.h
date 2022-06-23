#ifndef I2C_CONNECT_H
#define I2C_CONNECT_H

#include <Arduino.h>
#include "context_data.h"

class I2C {
    public:
        I2C(ContextData* context);
        
        void receiveThrust();
        void receiveAngle();

        void sendDataToArd1();
        void sendDataToArd2();
        void receiveFromArd1();
        void receiveFromArd2();

    private:
        ContextData* context;

        int ard1_addr = 8;
        int ard2_addr = 9;
      
};


#endif
