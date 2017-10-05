#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

/* Constants */
#include "keys.h"
#include "functions.h"
#include "logger.h"
#include "awsiot.h"

/* DHT22 */
#include "igrometer.h" // dht22 control functions
Igrometer Igro("/things/Temperature/shadow");

//#define FANPIN1 D6
//#define FANPIN2 D5
//#define IRRIGATION_TIME 6 // about 100ml



void setup() {
  setupIO();
  connectWifi();
}

char mybuffer[10];
double temp = 0;
int lightLevel;

void loop() {
  // put your main code here, to run repeatedly:
  delay(57000);
  Serial.println("Temperature:");
  temp = Igro.getTemperature(false);
  Serial.println(ftoa(temp, mybuffer, 2));
  delay(1000);
  Serial.println("Humidity:");
  temp = Igro.getHumidity();
  Serial.println(ftoa(temp, mybuffer, 2));
  delay(1000);
  Serial.println("Light:");
  lightLevel = Igro.getLightLevel();
  Serial.println(lightLevel);
  delay(1000);
  Serial.println("HI:");
  temp = Igro.getHeatIndex();
  Serial.println(temp);
}
