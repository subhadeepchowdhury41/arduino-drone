#ifndef SPI_GET_H
#define SPI_GET_H
#include <Arduino.h>
#include <get_pid.h>

class SPISlave {
  private:
      char rxMsg[20] = "";
      volatile bool flag1;
      bool flag2;
  public:
      SPISlave();
      ISR(SPI_STC_vector);
      void updatePID(PID* pid);
};

#endif