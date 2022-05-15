#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Arduino.h>

const char* ssid = "Galaxy M3145A2";
const char* password = "subha12345";

class Wifi {
    private:
        ESP8266WebServer server(80);
    public:
        Wifi();
        void connect();

};