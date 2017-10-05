#ifndef IGROMETER_H_
#define IGROMETER_H_

#include "awsiot.h"
#include "logger.h"

class Igrometer : public Thing {
private:
  char* getUrl(const char* path);
public:
  float temperature;
  float humidity;
  int lightLevel;
  float heatIndex;
  Igrometer(const char *awsPath);
  float getTemperature(bool isFarenheit);
  float getHumidity();
  int getLightLevel();
  float getHeatIndex();
};

#endif
