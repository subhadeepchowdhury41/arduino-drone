#include "Wire.h"
#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>
#include <ArduinoJson.h>

const int s1 = D3;
const int s2 = D4;
const int s3 = D5;

bool on = false;

int16_t pitch, roll, yaw, thrust;

byte a, b, c, d, e, f, g, h;

unsigned int timer = 0;
unsigned int switch_timer = 0;

const char* ssid = "Galaxy M3145A2";
const char* pass = "subha12345";

WebSocketsClient webSocket;
StaticJsonDocument<100> jsonData;
StaticJsonDocument<100> inData;
String jsonString;

void setUpWifi() {
  WiFi.begin(ssid, pass);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");
  Serial.println(WiFi.localIP());
}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  if (type == WStype_TEXT) {
    DeserializationError error = deserializeJson(inData, payload); // deserialize incoming Json String
    if (error) { // Print erro msg if incomig String is not JSON formated
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      return;
    }
    // webSocket.sendTXT("OK");
  } else if (type == WStype_CONNECTED) {
    Serial.println("WS: CONNECTED");
  }
}

void setUpWebSocket() {
  webSocket.begin("192.168.85.66", 81, "/");
  webSocket.onEvent(webSocketEvent);
  webSocket.setReconnectInterval(10000);
}

void setup() {
  Serial.begin(9600);
  setUpWifi();
  setUpWebSocket();
  Wire.begin(D1, D2);
  pinMode(s1, INPUT);
  pinMode(s2, INPUT);
  pinMode(s3, OUTPUT);
}

void loop() {
  timer = millis();

  if (!digitalRead(s1)) {
    if (millis() - switch_timer > 100) {
      on = !on;
      digitalWrite(s3, on ? HIGH : LOW);
      while(!digitalRead(s1)) {}
      switch_timer = millis();
    }
  } else {
    switch_timer = millis();
  }

  Wire.requestFrom(8, 8); /* request & read data of size 13 from slave */

  a = Wire.read();
  b = Wire.read();
  c = Wire.read();
  d = Wire.read();
  e = Wire.read();
  f = Wire.read();
  g = Wire.read();
  h = Wire.read();
  
  pitch = a;
  pitch = (pitch << 8) | b;

  roll = c;
  roll = (roll << 8) | d;

  yaw = e;
  yaw = (yaw << 8) | f;

  thrust = g;
  thrust = (thrust << 8) | h;

  JsonObject object = jsonData.to<JsonObject>();

  object["s"] = on;
  object["t"] = thrust < 0 ?  510 : thrust;
  object["p"] = pitch < 0 ? 510 : pitch;
  object["r"] = roll < 0 ? 510 : roll;
  object["y"] = yaw < 0 ? 510 : yaw;

  serializeJson(jsonData, jsonString);
  Serial.print(jsonString); Serial.print(" ");
  Serial.println(jsonString.length());

  webSocket.sendTXT(jsonString);

  jsonString = "";

  webSocket.loop();
  Serial.println(millis() - timer);
}