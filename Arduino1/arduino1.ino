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
  Serial.begin(9600);
  thrust = new Thrust();
  motors = new Motors(3, 5, 6, 9);
  pid = new PID();
  
//  slave = new SPISlave();
}

void loop() {
//  slave->updatePID(pid);
  thrust->setThrust(1300, 1300, 1300, 1300);
  String str = thrust->getThrustString();
  motors->setThrustFromThrust(thrust);
  Serial.println(str.length());
}

//ISR (SPI_STR_vector) {
//  slave->isDataComing();
//}
