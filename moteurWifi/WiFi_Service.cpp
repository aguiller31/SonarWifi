/*********************************************************************
 * @file  WiFi_Service.cpp
 * @author Guillermin Antoine et Paul Gadanho
 * @brief Implémentation de la classe WifiService.
 *********************************************************************/

#include "WiFi_Service.h"

/**
 * @brief Constructeur par défaut de la classe WifiService.
 */
WifiService::WifiService()
{

}

/**
 * @brief Constructeur de la classe WifiService avec des identifiants personnalisés.
 * @param ssid Le SSID du réseau WiFi.
 * @param passwd Le mot de passe du réseau WiFi.
 */
WifiService::WifiService(String ssid, String passwd)
{
  this->ssid = ssid;
  this->passwd = passwd;
}

/**
 * @brief Destructeur de la classe WifiService.
 * Déconnecte WiFi et affiche un message de destruction.
 * @throw std::runtime_error si la déconnexion WiFi échoue.
 */
WifiService::~WifiService()
{
  WiFi.disconnect();
  Serial.println("La classe Wifi a été détruite");
}

/**
 * @brief Démarre la connexion WiFi en utilisant les identifiants prédéfinis (SSID et mot de passe).
 * Attend la connexion et affiche l'adresse IP une fois connecté.
 * @throw std::runtime_error si la connexion WiFi échoue.
 */
void WifiService::start()
{
  WiFi.begin(this->ssid, this->passwd);
  Serial.println("Connexion en cours");
  
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() != WL_CONNECTED) {
    throw std::runtime_error("Échec de la connexion WiFi");
  }

  Serial.print("Connecté au réseau WiFi avec l'adresse IP : ");
  Serial.println(WiFi.localIP());
}

/**
 * @brief Se connecte au WiFi en utilisant les identifiants prédéfinis (SSID et mot de passe).
 * Attend la connexion et affiche l'adresse IP une fois connecté.
 * @throw std::runtime_error si la configuration du point d'accès échoue.
 */
void WifiService::connect()
{
  IPAddress local_IP(192,168,4,22);
  IPAddress gateway(192,168,4,9);
  IPAddress subnet(255,255,255,0);
  
  if (!WiFi.softAPConfig(local_IP, gateway, subnet)) {
    throw std::runtime_error("Échec de la configuration du point d'accès WiFi");
  }

  if (!WiFi.softAP(this->ssid.c_str(), this->passwd.c_str())) {
    throw std::runtime_error("Échec de la connexion au point d'accès WiFi");
  }

  Serial.print("Soft-AP IP address = ");
  Serial.println(WiFi.softAPIP());
}
