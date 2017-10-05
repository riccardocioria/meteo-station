#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include "keys.h"

extern const int led = LED_BUILTIN;

/******* SETUP *******/
void setupIO() {
  Serial.begin(9600);
  Serial.println("Started!");
}
/***** END SETUP *****/



/******* WIFI *******/
void printWiFiData() {
  // IP address
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // MAC address
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
  Serial.print(mac[5], HEX);
  Serial.print(":");
  Serial.print(mac[4], HEX);
  Serial.print(":");
  Serial.print(mac[3], HEX);
  Serial.print(":");
  Serial.print(mac[2], HEX);
  Serial.print(":");
  Serial.print(mac[1], HEX);
  Serial.print(":");
  Serial.println(mac[0], HEX);
}

void printCurrentNetwork() {
  // SSID
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // signal strength:
  Serial.print("signal strength (RSSI): ");
  Serial.println(WiFi.RSSI());
}

void setHostname() {
  if (MDNS.begin("meteostation")) {
    Serial.println("MDNS responder started");
  }
}

void connectWifi() {
  Serial.println();
  Serial.print("Connecting to ");
  Serial.print(wifiSsid);
  Serial.println("...");

  // Start blink green led until ESP8266 is not connected to wi-fi
  digitalWrite(led, HIGH);
  int blynk = 1;
  
  WiFi.begin(wifiSsid, wifiPwd);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");

    digitalWrite(led, ++blynk % 2);
    delay(100);
  }

  digitalWrite(led, HIGH);
  Serial.println("");
  Serial.println("WiFi connected");

  setHostname();
  printCurrentNetwork();
  printWiFiData();
}
/***** END WIFI *****/



/***** UTILITY *****/
char *ftoa(double f, char *a, int precision)
{
  long p[] = {0,10,100,1000,10000,100000,1000000,10000000,100000000};
  
  char *ret = a;
  long heiltal = (long)f;
  itoa(heiltal, a, 10);
  while (*a != '\0') a++;
  *a++ = '.';
  long desimal = abs((long)((f - heiltal) * p[precision]));
  itoa(desimal, a, 10);
  return ret;
}
/***** END UTILITY *****/
