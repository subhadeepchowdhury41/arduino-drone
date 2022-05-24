#ifndef WIFI_SERVER_H
#define WIFI_SERVER_H

#include <ESP8266WiFi.h>
#include "ESPAsyncWebServer.h"
#include <Arduino.h>

const char* ssid = "Galaxy M3145A2";
const char* password = "subha12345";

class WifiServer {
    private:
        ESPAsyncWebServer server(80);
        void handleRoot();
        void handleOnNotFound();
        void setUpServer();
        String getAngles();
        String getPids();
        String getThrusts();
        String getPing();
    public:
        WifiServer();
};

#endif