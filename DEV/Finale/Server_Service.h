#ifndef SERVER_SERVICE
#define SERVER_SERVICE
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h> 
class ServerService{
  public:
    ServerService(void);
    void setup(void);
    void start(void);
    void sendEvent(char,int);
  private:
    AsyncWebServer  server;
    AsyncEventSource events;
};
#endif