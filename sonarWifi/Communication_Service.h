#ifndef COMMUNICATION_SERVICE
#define COMMUNICATION_SERVICE
#include "WiFi_Service.h"
class CommunicationService{
  public:
    CommunicationService();
    void startWiFI();
  private:
    WifiService wifi;
    char *ssid;
    char *password;
};
#endif