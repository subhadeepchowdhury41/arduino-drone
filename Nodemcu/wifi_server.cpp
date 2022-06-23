#include "wifi_server.h"

const char* ssid = "Galaxy M3145A2";
const char* password = "subha12345";

ContextData* ctx;

WifiServer::WifiServer(ContextData* context) {
    ctx = context;
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    IPAddress ip = WiFi.localIP();
    Serial.println("");
    Serial.print("Connected to: ");
    Serial.println(ip);
    Serial.println("Setting up the server...");
    setUpServer();
}

String getAngles() {
    return ctx->getCurrAngles();
}

String getPIDs() {
    return "500500";
}

String getThrusts() {
    return ctx->getCurrThrusts();
}

String getPing() {
    return "100";
}

AsyncWebServer server(80);

void WifiServer::setUpServer() {

    // GET Methods
    server.on("/getAngles", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/plain", getAngles().c_str());
    });  // get angle
    server.on("/getPid", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/plain", getPIDs().c_str());
    });  // get pid
    server.on("/getThrusts", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/plain", getThrusts().c_str());
    });  // get thrusts
    server.on("/ping", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/plain", getPing().c_str());
    });

    // POST Methods
//     server.on("/setThrust", HTTP_POST, [](AsyncWenbServerRequest *request) {
//         request->send_P(200, "text/plain", setThrust);
//     });  // sets thrust

//     server.on("/setPitchRollYaw", HTTP_POST, [](AsyncWenbServerRequest *request) {
//         request->send_P(200, "text/plain", setPitchRollYaw);
//     });  // sets raw, pitch and yaw

    server.begin();
    Serial.println("Successfully started the server"); 
 }
