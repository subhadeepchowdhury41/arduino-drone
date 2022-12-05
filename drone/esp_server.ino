#include <WebSocketsServer.h>
#include <ESP8266WebServer.h>
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include "Wire.h"

const char* ssid = "Galaxy M3145A2";
const char* pass = "subha12345";

IPAddress local_IP(192, 168, 85, 66);
IPAddress gateway(192, 168, 1, 1);
IPAddress primaryDNS(8, 8, 8, 8);
IPAddress secondaryDNS(8, 8, 4, 4);

ESP8266WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

byte data[8];
StaticJsonDocument<100> jsonData;
StaticJsonDocument<100> spiData;
String message = "";
String spiString = "";
char dataBuff[40];
int temp;
int16_t spi_temp;

bool on = false;
bool prev_on = false;

int16_t req_th = 126, req_p = 382;
int16_t req_r = 638, req_y = 894;

const int data_led = D0;
const int on_output = D3;
const int wifi_led = D4;
const int spi_led = D1;

int timer = 0;

void setUpWifi() {
  WiFi.begin(ssid, pass);

  if(!WiFi.config(local_IP, gateway, primaryDNS, secondaryDNS)) {
    Serial.print('STA Configuration Successful!');
  } else {
    Serial.print('STA Configuration Failed!');
  }

  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");
  Serial.println(WiFi.localIP());
}


void webSocketEvent(byte num, WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.print("WS Type ");
      Serial.print(type);
      Serial.println(": DISCONNECTED");
      digitalWrite(wifi_led, LOW);
      break;
    case WStype_CONNECTED:
      Serial.print("WS Type ");
      Serial.print(type);
      Serial.println(": CONNECTED");
      digitalWrite(wifi_led, HIGH);
      break;
    case WStype_TEXT:
      DeserializationError error = deserializeJson(jsonData, payload);
      if (error) {
        Serial.print(F("Deserialization Failed"));
        Serial.println(error.c_str());
        return;
      }

      prev_on = on;
      on = jsonData["s"];
      req_th = jsonData["t"];
      req_p = jsonData["p"];
      req_r = jsonData["r"];
      req_y = jsonData["y"];

      if (prev_on != on) {
        digitalWrite(on_output, on ? HIGH : LOW);
      }

      // Serial.print(data[0]); Serial.print(" ");
      // Serial.print(data[1]); Serial.print(" ");
      // Serial.print(data[2]); Serial.print(" ");
      // Serial.print(data[3]); Serial.println();

      temp = map(req_th, 0, 1023, 0, 98);

      String message = "<" + String(map(req_th, 0, 1023, 0, 98)) + "," + String(map(req_p, 0, 1023, 0, 98)) +  + "," + String(map(req_r, 0, 1023, 0, 98)) + "," + String(map(req_y, 0, 1023, 0, 98)) + ">";

      Serial.println(message);

      byte plain[message.length() + 1];
      message.getBytes(plain, message.length() + 1);

      for (int i = 0; i < message.length() + 1; i++) {
        SPI.transfer(plain[i]);
      }
      
      break;
  }
}

void setup() {

  pinMode(wifi_led, OUTPUT);
  pinMode(spi_led, OUTPUT);
  pinMode(data_led, OUTPUT);
  pinMode(on_output, OUTPUT);

  digitalWrite(wifi_led, LOW);
  digitalWrite(spi_led, LOW);
  digitalWrite(data_led, LOW);
  digitalWrite(on_output, LOW);

  Serial.begin(9600);
  setUpWifi();
  server.begin();
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
  SPI.begin();

  timer = millis();
}

void loop() {
  webSocket.loop();
}