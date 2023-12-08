/*********************************************************************
 * @file  Apllication.h
 * @author Guillermin Antoine et Paul Gadanho
 * @brief Fichier header de l'application
 *********************************************************************/
#ifndef APPLICATION_H_
#define APPLICATION_H_
#define LIDAR_SSID "LidarSonarWifi"
#define LIDAR_PASSWORD "987654321"
#include <iostream>
#include <Arduino.h>
#include "WiFi_Service.h"
#include "Server_Service.h"
#include "Lidar_Service.h"

/**
  * @class Application
  * @brief Classe Application 
*/    
class Application
{
  public :
    /**
     * @fn Application();
     * @brief Constructeur par defaut
    */    
    Application();

    /**
     * @fn ~Application();
     * @brief Destructeur
    */    
    ~Application();   

    /**
     * @fn void init(void)
     * @brief Fonction d'initialisation de l'application
    */
    void init(void);

    /**
     * @fn void run(void)
     * @brief Fonction de lancement de l'application
    */
    void run(void);

    private:
      WifiService wifi;
      LIDARService LiDAR;
      ServerService server;

      unsigned long previousMillis;
      int prev_angle;

};

#endif