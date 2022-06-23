#include "i2c_connect.h" 

Thrust* thr;

void requestEvent() {
    String str = thr->getThrustString();
    char buff[20];
    str.toCharArray(buff, 20);
    Wire.write(buff, 20);
}

void receiveEvent(int size) {
    char buffer[50];
    int i = 0;
    while (Wire.available() > 0 && i < size) {
        char c = Wire.read();
        i++;
    }

    Serial.println(String(buffer));

    if (size) {
        if (size == 9) {
            
        } else if (size == 8) {
            Serial.println(buffer);
        } else if (size == 4) {

        }
    }
}

I2C::I2C(Thrust* thrust) {
    thr = thrust;
    Wire.begin(8);
    Wire.onReceive(receiveEvent);
    Wire.onRequest(requestEvent);
}

void setThrust() {
  
}
