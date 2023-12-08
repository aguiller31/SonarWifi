/*********************************************************************
 * @file  Apllication.h
 * @author Guillermin Antoine et Paul Gadanho
 * @brief Fichier header de l'application
 *********************************************************************/
#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <Arduino.h>
#include "WiFi_Service.h"
#include "Motor_Service.h"
#include "Client_Service.h"

#define LIDAR_SSID "LidarSonarWifi"
#define LIDAR_PASSWORD "987654321"

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
      MotorService motor;
      ClientService client;
};

#endif