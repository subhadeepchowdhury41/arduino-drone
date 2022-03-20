#include "get_pid.h"

PID::PID() {
  pid1 = 0;
  pid2 = 0;
}

PID::updateFromSPI(String code) {
  String sub1 = code.substring(0, 4);
  String sub2 = code.substring(4, 8);

//          pid1 = pid2 = 1500;
//          
//          Serial.print(rxMsg);
//          Serial.print(" ");
//          Serial.print(pid1);
//          Serial.print(" ");
//          Serial.print(pid2);
//          Serial.println(" ");
          
  pid1 = map(sub1.toInt(), 1000, 2000, -200, 200);
  pid2 = map(sub2.toInt(), 1000, 2000, -200, 200);
}
