#include "spi_get.h"
#include "get_pid.h"

SPISlave::SPISlave() {
  flag1 = false;
  flag2 = false;

  pinMode(SS, INPUT_PULLUP);
  pinMode(MOSI, OUTPUT);
  SPCR |= _BV(SPE);
  SPI.attachInterrupt();
  
}

void SPISlave::updatePID(PID* pid) {
  while (flag1 != false) {
    if (flag1 == true) {
      if (flag2 == false) {
        char q = SPDR;
        if (q == '<') {
          flag2 = true;
          flag1 = false;
        }
      } else {
        if (SPDR == '>') {
          flag1 = false;
          flag2 = false;
          i = 0;
          pid->updateFromSPI(String(rxMsg));
        } else {
          rxMsg[i] = SPDR;
          i++;
          flag1 = false;
        }
      }
    }
  }
}

void SPISlave::isDataComing() {
  flag1 = true;
}