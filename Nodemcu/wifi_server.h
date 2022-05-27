#ifndef WIFI_SERVER_H
#define WIFI_SERVER_H

#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <Arduino.h>

class WifiServer {
    private:
        void handleRoot();
        void handleOnNotFound();
        void setUpServer();
//        String getAngles();
        String getPIDs();
        String getThrusts();
        String getPing();
    public:
        WifiServer();
};

#endif
