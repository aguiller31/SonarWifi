/*********************************************************************
 * @file  Apllication.cpp
 * @author aguiller@insa-toulouse.fr
 * @brief Fichier source de l'application
 *********************************************************************/
#include "Application.h"
#include "Communication_Service.h"

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
  CommunicationService comm;
  comm.startWiFI();
}


void Application::run(void)
{
  // Code
    ;
}
