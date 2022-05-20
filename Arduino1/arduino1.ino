#include "control_esc.h"
#include "get_pid.h"
#include "spi_get.h"
#include "thrust.h"
#include "i2c_connect.h"

Motors* motors;
PID* pid;
SPISlave* slave;
Thrust* thrust;
I2C* i2c;

void setup() {
  motors = new Motors(3, 5, 6, 9);
  pid = new PID();
  slave = new SPISlave();
  motors->calibrateEsc();
}

void loop() {
  slave->updatePID(pid);
  motors->setThrustFromThrust(thrust);
}

ISR (SPI_STR_vector) {
  slave->isDataComing();
}