/*********************************************************************
 * @file  Apllication.cpp
 * @author aguiller@insa-toulouse.fr
 * @brief Fichier source de l'application
 *********************************************************************/
#include "Application.h"


Application::Application()
{
  // Code
  ; 
}
  
Application::~Application()
{
  // Code
  ;
}  

void Application::init(void)
{
  char * ssid = "PaulEtAntoine";
  char * password = "987654321";

  char report[64];
  //VL53L4CD_Result_t results;
  CommunicationService comm;
  comm.startWiFI(ssid, password);

  LIDARService LIDAR;
  LIDAR.setup();
  while(1){
    LIDAR.measure();
  
    snprintf(report, sizeof(report), "Status = %3u, Distance = %5u mm, Signal = %6u kcps/spad\r\n",
             LIDAR.getRangeStatus(),
             LIDAR.getDistance(),
             LIDAR.getSignalRatePerSpadKcps());
             
            
    Serial.print(report);
  }
}


void Application::run(void)
{
  // Code
    ;
}
