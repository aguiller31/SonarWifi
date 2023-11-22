
#include "application.h"
Application app;
void setup() {
  // put your setup code here, to run once:
  //appel a la fonction setup du porgramme principal ici uniquement
  app.setup();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  //appel a la fonction lopp du porgramme principal ici uniquement
  app.loop();
}
