#include "Communication_Service.h"
#include <Arduino.h>
CommunicationService::CommunicationService()
{
this->ssid = "PaulEtAntoine";
this->password = "987654321";
}
void CommunicationService::startWiFI()
{
  Serial.begin(9600);
  WifiService Wifi_service;
  Wifi_service.setup(this->ssid,this->password);
}