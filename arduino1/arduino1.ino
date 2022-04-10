#include "control_esc.h"
#include "get_pid.h"
#include "spi_get.h"

Motors* motors;
PID* pid;
SPISlave* slave;

void setup() {
  motors = new Motors(3, 5, 6, 9);
  pid = new PID();
  slave = new SPISlave();

  motors->calibrateEsc();
}

void loop() {
  slave->updatePID(pid);
}
