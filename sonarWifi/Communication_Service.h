#ifndef COMMUNICATION_SERVICE
  #define COMMUNICATION_SERVICE
  #include "WiFi_Service.h"
  #include "Server_Service.h" 
  class CommunicationService{
    public:
      CommunicationService();
      CommunicationService(char  *, char *);
      void startWiFI();
      void startServer();
      void sendEvent(char,int);
    private:
      WifiService wifi;
      ServerService server;
  };
#endif