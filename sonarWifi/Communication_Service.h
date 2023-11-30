#ifndef COMMUNICATION_SERVICE
#define COMMUNICATION_SERVICE
#include "WiFi_Service.h"
class CommunicationService{
  public:
    CommunicationService();
    void startWiFI(char  *, char *);
  private:
    WifiService wifi;
};
#endif