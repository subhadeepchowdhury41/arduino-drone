#include "control_esc.h"

#define MAX_THR 2000
#define MIN_THR 1000

Motors::Motors(int p1, int p2, int p3, int p4) {
  
  m1.attach(p1);
  m2.attach(p2);
  m3.attach(p3);
  m4.attach(p4);

  calibrateEsc();
}

void Motors::setThrustFromThrust(Thrust* thrust) {
  
  m1.writeMicroseconds(thrust->t1);
  m2.writeMicroseconds(thrust->t2);
  m3.writeMicroseconds(thrust->t3);
  m4.writeMicroseconds(thrust->t4);

}

void Motors::sendSignal(int t) {
  m1.writeMicroseconds(t);
  m2.writeMicroseconds(t);
  m3.writeMicroseconds(t);
  m4.writeMicroseconds(t);
}

void Motors::calibrateEsc() {
  Serial.println("Sending maximum output");
  sendSignal(MAX_THR);
  delay(5000);
  Serial.println("Sending minimum output");
  sendSignal(MIN_THR);
  delay(5000);
  Serial.println("Done calibrating");
}
