/*********************************************************************
 * @file  WiFi_Service.h
 * @author Guillermin Antoine et Paul Gadanho
 * @brief Définition de la classe WifiService.
 *********************************************************************/

#ifndef WIFI_SERVICE
#define WIFI_SERVICE

#include <ESP8266WiFi.h>
#include <stdexcept>

/**
 * @class WifiService
 * @brief Classe WifiService Gère les fonctionnalités liées à la connexion WiFi.
 */
class WifiService {
  public:
    /**
     * @brief Constructeur par défaut de la classe WifiService.
     */
    WifiService(void);

    /**
     * @brief Constructeur de la classe WifiService avec des identifiants personnalisés.
     * @param ssid Le SSID du réseau WiFi.
     * @param passwd Le mot de passe du réseau WiFi.
     */
    WifiService(String ssid, String passwd);

    /**
     * @brief Destructeur de la classe WifiService.
     */
    ~WifiService(void);

    /**
     * @brief Démarre la connexion WiFi en utilisant les identifiants prédéfinis (SSID et mot de passe).
     * Attend la connexion et affiche l'adresse IP une fois connecté.
     */
    void start(void);

    /**
     * @brief Se connecte au WiFi en utilisant les identifiants prédéfinis (SSID et mot de passe).
     * Attend la connexion et affiche l'adresse IP une fois connecté.
     */
    void connect(void);

  private:
    String ssid; ///< Le SSID du réseau WiFi.
    String passwd; ///< Le mot de passe du réseau WiFi.
};

#endif
