#include "thrust.h"

Thrust::Thrust() {
  t1 = 1000;
  t2 = 1000;
  t3 = 1000;
  t4 = 1000;
}

void Thrust::setThrust(int t1, int t2, int t3, int t4) {
  this->t1 = t1;
  this->t2 = t2;
  this->t3 = t3;
  this->t4 = t4;
}

String Thrust::getThrustString() {
  char s1[20];
  char s2[5];
  
  itoa(t1, s1, 10);
  
  itoa(t2, s2, 10);
  strcat(s1, s2);

  itoa(t3, s2, 10);
  strcat(s1, s2);

  itoa(t4, s2, 10);
  strcat(s1, s2);

  return String(s1);
  
}
