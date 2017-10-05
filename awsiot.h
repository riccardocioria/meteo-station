#ifndef AWSIOT_H_
#define AWSIOT_H_

#include "logger.h"
#include <AmazonIOTClient.h>
#include <Esp8266AWSImplementations.h>
#include <AWSFoundationalTypes.h>

class Thing : public Logger {
public:
  const char *awsPath;
  AmazonIOTClient iotClient;
  Thing(const char *awsPath);
  void updateShadow(MinimalString data);
private:
  Esp8266HttpClient httpClient;
  Esp8266DateTimeProvider dateTimeProvider;
};

#endif
