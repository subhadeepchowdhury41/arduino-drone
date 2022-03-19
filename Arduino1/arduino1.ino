#include "control_esc.h"

Motors* motors;

void setup() {
  motors = new Motors(3, 5, 6, 9);
  motors->calibrateEsc();
}

void loop() {
  
}
