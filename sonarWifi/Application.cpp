/*********************************************************************
 * @file  Apllication.cpp
 * @author aguiller@insa-toulouse.fr
 * @brief Fichier source de l'application
 *********************************************************************/
#include "Application.h"


Application::Application():communication(),LiDAR(),motor()
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
  char report[64];
  Serial.begin(9600);
  while(!Serial){} // Waiting for serial connection
  communication.startWiFI();
  communication.startServer();


  LiDAR.setup();
  motor.setup();
  motor.start();
  /*while(1){
    LiDAR.measure();
  
    snprintf(report, sizeof(report), "Status = %3u, Distance = %5u mm, Signal = %6u kcps/spad\r\n",
             LiDAR.getRangeStatus(),
             LiDAR.getDistance(),
             LiDAR.getSignalRatePerSpadKcps());
             
            
    Serial.print(report);
  }*/
}


void Application::run(void)
{
  LiDAR.measure();
  communication.sendEvent('d',LiDAR.getDistance());
  motor.
   communication.sendEvent('d',"LiDAR.getDistance());
}
