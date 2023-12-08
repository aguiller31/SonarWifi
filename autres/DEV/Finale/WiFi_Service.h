#ifndef WIFI_SERVICE
#define WIFI_SERVICE
#include <ESP8266WiFi.h>
class WifiService {
  public:
    WifiService();
    WifiService(char *, char *);
    void setup();
  private:
    char * ssid;
    char * passwd;
};

#endif