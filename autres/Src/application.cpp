#include "application.h"
#include "Debug_Service.h"
#include "Communication_Service.h"
Application::Application()
{

}
void Application::setup()
{
  DebugService debug(9600);
  debug.println("Hello World");
  CommunicationService comm;
  comm.startWiFI();
}
void Application::loop()
{
  
}