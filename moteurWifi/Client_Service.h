/*********************************************************************
 * @file  Client_Service.h
 * @author Guillermin Antoine et Paul Gadanho
 * @brief Définition de la classe ClientService.
 *********************************************************************/

#ifndef CLIENT_SERVICE
#define CLIENT_SERVICE

#include <Arduino.h>
#include <AsyncHTTPRequest_Generic.hpp>

/**
  * @class ClientService
  * @brief Classe ClientService Permet l'envoie de l'angle au serveur
*/  
class ClientService : public AsyncHTTPRequest{ //héritage
  public:
    /**
     * @brief Constructeur de la classe ClientService.
     * @param url L'URL du service distant.
     */
    ClientService(String);

    /**
     * @brief Destructeur de la classe ClientService.
     */
    ~ClientService(void);

    /**
     * @brief Envoie un angle au service distant.
     * @param angle L'angle à envoyer.
     */
    void sendAngle(int);

    /**
     * @brief Initialise l'instance ClientService.
     *        Configure les paramètres nécessaires, tels que la désactivation du débogage.
     */
    void setup();

  private:
    String url; ///< L'URL du service distant.
};

#endif
