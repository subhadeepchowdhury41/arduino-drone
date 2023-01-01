#include <Wire.h>

const int p1 = A0;
const int p2 = A1;
const int p3 = A2;
const int p4 = A3;

byte data[8];
int16_t pitch, roll, yaw, thrust;
unsigned int timer = 0;

void setup() {
  Wire.begin(8);
  Wire.onRequest(requestEvent);
  Serial.begin(115200);
}

void loop() {
  // timer = millis();

  Serial.print(thrust); Serial.print(" "); Serial.print(pitch); Serial.print(" ");
  Serial.print(roll); Serial.print(" "); Serial.print(yaw); Serial.print(" ");

  Serial.println("");
  // delay(100);
  // Serial.println(millis() - timer);
}

void requestEvent() {
  pitch = pitch*0.8 + 0.2*analogRead(p1);
  roll = roll*0.8 + 0.2*analogRead(p2);
  yaw = yaw*0.8 + 0.2*analogRead(p3);
  thrust = thrust*0.8 + 0.2*analogRead(p4);


  data[0] = (pitch >> 8) & 0xFF;
  data[1] = pitch & 0xFF;

  data[2] = (roll >> 8) & 0xFF;
  data[3] = roll & 0xFF;

  data[4] = (yaw >> 8) & 0xFF;
  data[5] = yaw & 0xFF;

  data[6] = (thrust >> 8) & 0xFF;
  data[7] = thrust & 0xFF;

  Wire.write(data, 8);
}