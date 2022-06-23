#ifndef WIFI_SERVER_H
#define WIFI_SERVER_H

#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <Arduino.h>
#include "context_data.h"

class WifiServer {
    public:
        void setUpServer();
        WifiServer(ContextData* context);
};

#endif
