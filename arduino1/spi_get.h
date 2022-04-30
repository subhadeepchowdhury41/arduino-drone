#ifndef SPI_GET_H
#define SPI_GET_H

#include <Arduino.h>
#include <SPI.h>
#include "get_pid.h"

class SPISlave {
  private:
      char rxMsg[20] = "";
      volatile bool flag1;
      bool flag2;
      int i;
  public:
      SPISlave();
      void isDataComing();
      void updatePID(PID* pid);
};

#endif