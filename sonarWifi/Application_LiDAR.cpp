/*********************************************************************
 * @file  Application.cpp
 * @brief Fichier source de l'application
 * @authors Guillermin Antoine et Paul Gadanho
 *********************************************************************/

#include "Application.h"

/**
 * @class Application
 * @brief Gère le fonctionnement global de l'application.
 * Cette classe coordonne la communication avec le LiDAR, le serveur, et d'autres composants.
 */

/**
 * @brief Constructeur de la classe Application.
 * Initialise les objets WifiService, ServerService et LiDARService.
 */
Application::Application(): wifi((String)LIDAR_SSID, (String)LIDAR_PASSWORD)
{
  this->previousMillis = millis();
  this->prev_angle = 0;
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
 * démarre la connexion WiFi, le serveur et configure le LiDAR.
 */
void Application::init(void)
{
  Serial.begin(9600);
  while(!Serial){} // On attend la connexion sur le port série

  try{
    this->wifi.connect();

    this->server.setup();
    this->server.start();

    this->LiDAR.setup();
  }
  catch (const std::exception& e) {
    Serial.println(e.what());
  }
}

/**
 * @brief Exécute le fonctionnement de l'application.
 * Mesure la distance du LiDAR et envoie les données au serveur si l'angle change.
 */
void Application::run(void)
{
  unsigned long currentMillis = millis();
  int angle = server.getAngle(); 
  if(this->prev_angle != angle){
      this->prev_angle = angle;
      if (currentMillis - this->previousMillis >= 100) {
        try{
          this->LiDAR.measure();
          this->server.sendEvent('d', this->LiDAR.getDistance());
        }
        catch (const std::exception& e) {
          Serial.println(e.what());
        }
        this->server.sendEvent('a', angle);
        this->previousMillis = currentMillis;
      }
  }
}
