#ifndef CONTROL_ESC_H
#define CONTROL_ESC_H

#include <Arduino.h>
#include <Servo.h>
#include "thrust.h"


class Motors {
  private:
      Servo m1, m2, m3, m4;
      void sendSignal(int t);
      void calibrateEsc();
  public:
      Motors(int p1, int p2, int p3, int p4);
      void setThrustFromThrust(Thrust* thrust);
};

#endif
