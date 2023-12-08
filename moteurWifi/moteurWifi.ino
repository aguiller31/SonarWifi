#include "Application.h"
#include <AsyncHTTPRequest_Generic.h> //on doit obligatoirement inclure ce fichier ici pour que l'inclusion fonctionne dans le service Client
Application myApplication;

void setup() 
{
  // put your setup code here, to run once:
  myApplication.init();
}

void loop() 
{
  // put your main code here, to run repeatedly:
  myApplication.run();
}
