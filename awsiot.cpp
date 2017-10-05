#include "awsiot.h"
#include "functions.h"
#include "keys.h"

Thing::Thing(const char *_awsPath) {
  this->d("Initializing IoT client...");
  awsPath = _awsPath;

  iotClient.setAWSRegion(awsIotRegion);
  iotClient.setAWSEndpoint(awsIotEndpoint);
  iotClient.setAWSDomain(awsIotDomain);
  iotClient.setAWSPath(awsPath); // "/things/button/shadow"
  iotClient.setAWSKeyID(awsKeyID);
  iotClient.setAWSSecretKey(awsSecKey);
  iotClient.setHttpClient(&httpClient);
  iotClient.setDateTimeProvider(&dateTimeProvider);

  delay(50);
}

void Thing::updateShadow(MinimalString data) {
  ActionError actionError;
  this->d("Updating thing shadow...");

  char dataComplete[150];
  sprintf(dataComplete, "{\"state\":{\"reported\":%s}}", data.getCStr());
  MinimalString shadow = String(dataComplete).c_str();
  char* result = iotClient.update_shadow(shadow, actionError);

  /*Serial.print("result: ");
  Serial.println(result);*/
}

