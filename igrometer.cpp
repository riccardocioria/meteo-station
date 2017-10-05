#include <AWSFoundationalTypes.h>

#include "igrometer.h"
#include "functions.h"
#include "keys.h"

#include "DHT.h"
#define DHTPIN D2     // what digital pin the DHT22 is conected to
#define DHTTYPE DHT22   // there are multiple kinds of DHT sensors
#define LIGHTPIN A0

DHT dht(DHTPIN, DHTTYPE);

Igrometer::Igrometer(const char *awsPath) : Thing(awsPath) {}


char* Igrometer::getUrl(const char* path) {
  char url[100];
  sprintf(url, "https://%s%s", awsIotDomain, path);
  return url;
}

// Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
float Igrometer::getTemperature(bool isFarenheit) {
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature(false);
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(t) || isnan(f)) {
      this->d("Failed to read from DHT sensor!");
      return -100;
  }

  // update aws shadow
  char json[100];
  char tempc[10];
  char tempf[10];
  sprintf(json, "{\"celsius\": %s, \"fahrenheit\": %s, \"kelvin\": 0}", ftoa(t, tempc, 2), ftoa(f, tempf, 2));
  MinimalString data = String(json).c_str();

  const char* path = "/things/Temperature/shadow";
  iotClient.setAWSEndpoint(this->getUrl(path));
  iotClient.setAWSPath(path);
  this->updateShadow(data);

  // change status
  temperature = t;
  
  if(isFarenheit) return f;
  return t;
}

float Igrometer::getHumidity() {
  float h = dht.readHumidity();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h)) {
      this->d("Failed to read from DHT sensor!");
      return -100;
  }

  // update aws shadow
  char json[100];
  char temp[10];
  sprintf(json, "{\"humidity\": %s}", ftoa(h, temp, 2));
  MinimalString data = String(json).c_str();

  const char* path = "/things/Humidity/shadow";
  iotClient.setAWSEndpoint(this->getUrl(path));
  iotClient.setAWSPath(path);
  this->updateShadow(data);
  
  humidity = h;
  return h;
}

int Igrometer::getLightLevel() {
  int sensorValue = analogRead(LIGHTPIN);
  
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float _lightLevel = sensorValue * (100 / 1023.0);
  lightLevel = (int)_lightLevel;

  // update aws shadow
  char json[30];
  sprintf(json, "{\"light\": %d}", lightLevel);
  MinimalString data = String(json).c_str();
  
  const char* path = "/things/Light/shadow";
  iotClient.setAWSEndpoint(this->getUrl(path));
  iotClient.setAWSPath(path);
  this->updateShadow(data);
  
  return lightLevel;
}

float Igrometer::getHeatIndex() {
  // Compute heat index in Celsius (isFahreheit = false)
  if(temperature && humidity) {
    float hic = dht.computeHeatIndex(temperature, humidity, false);
    heatIndex = hic;
    return hic;
  }
  else {
    return -100.0;
  }
}

