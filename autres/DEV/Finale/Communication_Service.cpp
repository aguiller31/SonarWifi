#include "Communication_Service.h"
#include <Arduino.h>
char * ssid = "PaulEtAntoine";
char * password = "987654321";
CommunicationService::CommunicationService():wifi(ssid,password)
{

}
void CommunicationService::startWiFI()
{
  this->wifi.setup();
}
void CommunicationService::startServer()
{
  this->server.setup();
  this->server.start();
}

void CommunicationService::sendEvent(char c, int n)
{
  this->server.sendEvent(c, n);
}