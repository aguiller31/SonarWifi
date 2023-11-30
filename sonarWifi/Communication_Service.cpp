#include "Communication_Service.h"
#include <Arduino.h>
CommunicationService::CommunicationService()
{

}
void CommunicationService::startWiFI(char  * ssid, char * passwd)
{
  Serial.begin(9600);
  while(!Serial){} // Waiting for serial connection
  WifiService Wifi_service(ssid,passwd);
  Wifi_service.setup();
}