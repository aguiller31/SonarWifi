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

  CommunicationService comm;
  comm.startWiFI(ssid, password);

  LIDARService LIDAR;
  LIDAR.setup();
}


void Application::run(void)
{
  // Code
    ;
}
