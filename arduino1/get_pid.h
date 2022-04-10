#ifndef GET_PID_H
#define GET_PID_H

#include <Arduino.h>

class PID {
  private:
      int pid1;
      int pid2;
  public:
      PID();
      void updateFromSPI(String code);
};

#endif
