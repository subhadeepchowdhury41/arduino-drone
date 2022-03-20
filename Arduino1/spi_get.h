#ifndef SPI_GET_H
#define SPI_GET_H

#include <Arduino.h>

class SPISlave {
  private:
      char rxMsg[20] = "";
      volatile bool flag1;
      bool flag2;
  public:
      SPISlave();
      String getPID();
};

#endif
