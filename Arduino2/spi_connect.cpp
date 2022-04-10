#include "spi_connect.h"
#include <SPI.h>
#include <Arduino.h>

SPIMaster::SPIMaster() {
    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV128);
    pinMode(SS, OUTPUT);
    digitalWrite(SS, LOW);
}