/*********************************************************************
 * @file  Application.cpp
 * @brief Fichier source de l'application
 * @authors Guillermin Antoine et Paul Gadanho
 *********************************************************************/

#include "Application.h"

/**
 * @brief Constructeur de la classe Application.
 * Initialise les objets WifiService, MotorService et ClientService.
 */
Application::Application(): wifi((String)LIDAR_SSID, (String)LIDAR_PASSWORD), motor(24), client("http://192.168.4.22/angle")
{
  ; // Corps vide du constructeur
}
  
/**
 * @brief Destructeur de la classe Application.
 * Affiche un message lors de la destruction de l'objet.
 */
Application::~Application()
{
  Serial.println("Destruction de l'application");
}  

/**
 * @brief Initialise l'application.
 * Configure la communication série, attend la connexion sur le port série,
 * démarre la connexion WiFi et configure le moteur.
 */
void Application::init(void)
{
  Serial.begin(9600);
  while(!Serial){} // On attend la connexion sur le port série

  this->wifi.start(); 
  this->motor.setup();
}

/**
 * @brief Exécute le fonctionnement de l'application.
 * Effectue une étape du moteur, récupère l'angle et envoie l'angle au service distant.
 */
void Application::run(void)
{
  int angle = this->motor.step();
  if(angle != -1){
    this->client.sendAngle(angle);
  }
}
