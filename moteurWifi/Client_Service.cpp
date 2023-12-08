/*********************************************************************
 * @file  Client_Service.cpp
 * @author Guillermin Antoine et Paul Gadanho
 * @brief Implémentation de la classe ClientService.
 *********************************************************************/

#include "Client_Service.h"

/**
 * @brief Constructeur de la classe ClientService.
 * @param url L'URL du service distant.
 */
ClientService::ClientService(String url)
{
  this->url = url;  
}

 /**
 * @brief Destructeur de la classe MotorService.
 */
ClientService::~ClientService(void){
  AsyncHTTPRequest::~AsyncHTTPRequest(); //on appelle le destructeur de la classe mère
  Serial.println("La classe Client a été détruite");
}

/**
 * @brief Initialise l'instance ClientService.
 *        Configure les paramètres nécessaires, tels que la désactivation du débogage.
 */
void ClientService::setup()
{
    this->setDebug(false); // Hérité de la classe AsyncHTTPRequest.
}

/**
 * @brief Envoie un angle au service distant.
 * @param angle L'angle à envoyer.
 */
void ClientService::sendAngle(int angle)
{
  static bool requestOpenResult;

  // Vérifie si la requête peut être envoyée.
  if (this->readyState() == readyStateUnsent || this->readyState() == readyStateDone)
  {
    // Construit l'URL avec l'angle fourni.
    String page = url + "?angle=" + String(angle);

    // Tente d'ouvrir la connexion HTTP.
    requestOpenResult = this->open("GET", page.c_str());

    // Si la connexion est ouverte avec succès, envoie la requête.
    if (requestOpenResult)
      this->send(); // Hérité de la classe AsyncHTTPRequest.
  }
}
