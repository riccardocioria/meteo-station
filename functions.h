#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

extern const int led;


void setupIO();
void printWiFiData();
void printCurrentNetwork();
void setHostname();
void connectWifi();
char *ftoa(double f, char *a, int precision);

#endif
