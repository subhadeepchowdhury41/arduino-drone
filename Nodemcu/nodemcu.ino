#include "i2c_connect.h"
#include "context_data.h"
#include "wifi_server.h"

ContextData* context;
WifiServer* wifiServer;
I2C* i2c;

void setup() {
  Serial.begin(9600);
  context = new ContextData();
  i2c = new I2C(context);
  wifiServer = new WifiServer(context);
}

void loop() {
  i2c->receiveFromArd1();
  // i2c->receiveFromArd2();
}
