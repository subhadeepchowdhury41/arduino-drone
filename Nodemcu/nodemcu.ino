#include "i2c_connect.h"
#include "wifi_server.h"

WifiServer* wifiServer;

void setup() {
  Serial.begin(9600);
    wifiServer = new WifiServer();
}

void loop() {

}
