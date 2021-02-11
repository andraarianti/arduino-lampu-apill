#define BLYNK_PRINT Serial  
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <SoftwareSerial.h>
#include <WiFi.h>

WiFiClient client;

//esp
char auth[] = "JXiSzECqTn-s44-qX40IJYUGibQIhmI7";
char ssid[] = "OPPO F11";
char pass[] = "lalala13";

const char* host = "blynk-cloud.com";
unsigned int port = 8080;

SoftwareSerial EspSerial(2, 3); // RX, TX

#define ESP8266_BAUD 9600
ESP8266 wifi(&EspSerial);


//lampu
int ledR1 = 2;
int ledY1 = 3;
int ledG1 = 4;
int ledR2 = 5;
int ledY2 = 6;
int ledG2 = 7;
int ledR3 = 8;
int ledY3 = 9;
int ledG3 = 10;
int animationSpeed = 0;
int dataserial;
int bangjo = 0;

bool httpRequest(const String& method,
                 const String& request,
                 String&       response)
{
  Serial.print(F("Connecting to "));
  Serial.print(host);
  Serial.print(":");
  Serial.print(port);
  Serial.print("... ");
  if (client.connect(host, port)) {
    Serial.println("OK");
  } else {
    Serial.println("failed");
    return false;
  }

  client.print(method); client.println(F(" HTTP/1.1"));
  client.print(F("Host: ")); client.println(host);
  client.println(F("Connection: close"));
  if (request.length()) {
    client.println(F("Content-Type: application/json"));
    client.print(F("Content-Length: ")); client.println(request.length());
    client.println();
    client.print(request);
  } else {
    client.println();
  }

  //Serial.println("Waiting response");
  int timeout = millis() + 5000;
  while (client.available() == 0) {
    if (timeout - millis() < 0) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return false;
    }
  }

  //Serial.println("Reading response");
  int contentLength = -1;
  while (client.available()) {
    String line = client.readStringUntil('\n');
    line.trim();
    line.toLowerCase();
    if (line.startsWith("content-length:")) {
      contentLength = line.substring(line.lastIndexOf(':') + 1).toInt();
    } else if (line.length() == 0) {
      break;
    }
  }

  //Serial.println("Reading response body");
  response = "";
  response.reserve(contentLength + 1);
  while (response.length() < contentLength && client.connected()) {
    while (client.available()) {
      char c = client.read();
      response += c;
    }
  }
  client.stop();
  return true;
}


void setup()
{
  Serial.begin(9600);
  delay(10);
  EspSerial.begin(ESP8266_BAUD);
  delay(10);
  Blynk.begin(auth, wifi, ssid, pass, "blynk-cloud.com", 8080);
  
  pinMode(ledR1, OUTPUT);
  pinMode(ledY1, OUTPUT);
  pinMode(ledG1, OUTPUT);
  pinMode(ledR2, OUTPUT);
  pinMode(ledY2, OUTPUT);
  pinMode(ledG2, OUTPUT);
  pinMode(ledR3, OUTPUT);
  pinMode(ledY3, OUTPUT);
  pinMode(ledG3, OUTPUT);
}

void loop()
{
  Blynk.run();

  String response;

 Serial.println("Reading value");

  if (httpRequest(String("GET /") + "JXiSzECqTn-s44-qX40IJYUGibQIhmI7" + "/get/V1", "", response)) {
    Serial.print("Value from server: ");
    Serial.println(response);
  }
  
}
