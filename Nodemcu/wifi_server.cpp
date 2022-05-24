#include "wifi_server.h"

WifiServer::WifiServer() {
    WiFi.softAP(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }

    IPAdress ip = WiFi.softAPIP();
    Serial.println("");
    Serial.print("Connected to: ")
    Serial.println(ip);

    Serial.println("Setting up the server...");
    setUpServer();
}

void WifiServer::setUpServer() {

    // GET Methods
    server.on("/getAngles", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/plain", getAngles());
    });  // get angle
    server.on("/getPid", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/plain", getPIDs());
    });  // get pid
    server.on("/getThrusts", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/plain", getThrusts());
    });  // get thrusts
    server.on("/ping", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/plain", getPing);
    })


    // POST Methods
//     server.on("/setThrust", HTTP_POST, [](AsyncWenbServerRequest *request) {
//         request->send_P(200, "text/plain", setThrust);
//     });  // sets thrust

//     server.on("/setPitchRollYaw", HTTP_POST, [](AsyncWenbServerRequest *request) {
//         request->send_P(200, "text/plain", setPitchRollYaw);
//     });  // sets raw, pitch and yaw
// }


String WifiServer::getAngles() {
    return "8080";
}


String WifiServer::getPIDs() {
    return "500500";
}

String WifiServer::getThrusts() {
    return "1000100010001000";
}

String WifiServer::getPing() {
    return "100";
}