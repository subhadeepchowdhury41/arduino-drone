#ifndef CONTROL_ESC_H
#define CONTROL_ESC_H

#include <Arduino.h>
#include <Servo.h>


class Motors {
  private:
      Servo m1, m2, m3, m4;
      void sendSignal(int t);
  public:
      char* thrustString();
      Motors(int p1, int p2, int p3, int p4);
      void calibrateEsc();
      void setThrust(int t1, int t2, int t3, int t4);
};

#endif
