/*********************************************************************
 * @file  Server_Service.h
 * @brief Définition de la classe ServerService.
 * @authors Guillermin Antoine et Paul Gadanho
 *********************************************************************/

#ifndef SERVER_SERVICE
#define SERVER_SERVICE

#include <Arduino.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h> 
#include <stdexcept>

/**
 * @class ServerService
 * @brief Gère le serveur web et les événements associés.
 * Cette classe utilise la bibliothèque ESPAsyncWebServer pour fournir des fonctionnalités de serveur web asynchrones.
 */
class ServerService : public AsyncWebServer {
  public:
    /**
     * @brief Constructeur de la classe ServerService.
     * Initialise le serveur web et les événements associés.
     */
    ServerService(void);

    /**
     * @brief Destructeur de la classe ClientService.
     */
    ~ServerService(void);

    /**
     * @brief Configure le serveur web et les routes.
     * Ajoute les routes pour servir la page HTML principale et recevoir des données d'angle.
     */
    void setup(void);

    /**
     * @brief Démarre le serveur web.
     */
    void start();

    /**
     * @brief Envoie un événement au client connecté via Server-Sent Events (SSE).
     * @param c Caractère représentant le type d'événement ('a' pour angle, 'd' pour distance, etc.).
     * @param distance Valeur de la distance à envoyer.
     */
    void sendEvent(char c, int distance);

    /**
     * @brief Obtient la valeur de l'angle.
     * @return La valeur de l'angle actuelle.
     */
    int getAngle(void);

  private:
    AsyncEventSource events; ///< Gère les événements Server-Sent Events (SSE).
    int angle; ///< Stocke la valeur actuelle de l'angle.
};

#endif
