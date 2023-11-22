#include "Communication_Service.h"
#include "WiFi_Service.h"
CommunicationService::CommunicationService()
{

}
void CommunicationService::startWiFI()
{
  char *ssid = "PaulEtAntoine";
  char *password = "987654321";
  WifiService Wifi_service;
  Wifi_service.setup(ssid,password);
}