/*********************************************************************
 * @file  Lidar_Service.cpp
 * @author Guillermin Antoine et Paul Gadanho
 * @brief Implémentation de la classe LIDARService.
 *********************************************************************/

#include "Lidar_Service.h"

/**
 * @class LIDARService
 * @brief Gère les fonctionnalités du capteur LIDAR VL53L4CD.
 * Cette classe fournit des méthodes pour configurer, mesurer et récupérer des données du capteur LIDAR.
 */

/**
 * @brief Constructeur de la classe LIDARService.
 * Initialise le capteur LIDAR VL53L4CD.
 */
LIDARService::LIDARService() : VL53L4CD(&Wire, D0)
{
}

/**
 * @brief Configure le capteur LIDAR.
 * Initialise le capteur, le configure et démarre la mesure.
 */
void LIDARService::setup()
{
  Wire.begin();
  this->begin();
  this->VL53L4CD_Off();
  this->InitSensor();
  this->VL53L4CD_SetRangeTiming(200, 0);
  this->VL53L4CD_StartRanging();
}

/**
 * @brief Effectue une mesure avec le capteur LIDAR.
 * Attend la disponibilité des nouvelles données et récupère le résultat.
 * Lance une exception en cas d'échec de la mesure.
 */
void LIDARService::measure()
{
  uint8_t NewDataReady = 0;
  uint8_t status;

  do {
    status = VL53L4CD_CheckForDataReady(&NewDataReady);
  } while (!NewDataReady);

  if ((!status) && (NewDataReady != 0)) {
    this->VL53L4CD_ClearInterrupt();
    this->VL53L4CD_GetResult(&(this->results));
  } else {
    throw std::runtime_error("Échec de la mesure LIDAR");
  }
}

/**
 * @brief Récupère la distance mesurée par le capteur LIDAR.
 * Ajuste la valeur pour assurer qu'elle est dans une plage valide.
 * @return La distance mesurée en millimètres.
 */
uint16_t LIDARService::getDistance(void)
{
  uint16_t distance_mm = this->results.distance_mm - 2;
  distance_mm = (distance_mm > 0) ? distance_mm : 0;
  distance_mm = (distance_mm > 2000) ? 0 : distance_mm;
  return distance_mm;
}

/**
 * @brief Récupère le statut de plage du capteur LIDAR.
 * @return Le statut de plage.
 */
uint8_t LIDARService::getRangeStatus(void)
{
  return this->results.range_status;
}

/**
 * @brief Récupère le taux ambiant par SPAD du capteur LIDAR.
 * @return Le taux ambiant par SPAD en kilo counts par seconde (kcps).
 */
uint16_t LIDARService::getAmbientRatePerSpadKcps(void)
{
  return this->results.ambient_per_spad_kcps;
}

/**
 * @brief Récupère le taux ambiant du capteur LIDAR.
 * @return Le taux ambiant en kilo counts par seconde (kcps).
 */
uint16_t LIDARService::getAmbientRateKcps(void)
{
  return this->results.ambient_rate_kcps;
}

/**
 * @brief Récupère le taux de signal du capteur LIDAR.
 * @return Le taux de signal en kilo counts par seconde (kcps).
 */
uint16_t LIDARService::getSignalRateKcps(void)
{
  return this->results.signal_rate_kcps;
}

/**
 * @brief Récupère le taux de signal par SPAD du capteur LIDAR.
 * @return Le taux de signal par SPAD en kilo counts par seconde (kcps).
 */
uint16_t LIDARService::getSignalRatePerSpadKcps(void)
{
  return this->results.signal_per_spad_kcps;
}

/**
 * @brief Récupère le nombre de SPAD du capteur LIDAR.
 * @return Le nombre de SPAD.
 */
uint16_t LIDARService::getNumberOfSpad(void)
{
  return this->results.number_of_spad;
}

/**
 * @brief Récupère l'écart-type en millimètres du capteur LIDAR.
 * @return L'écart-type en millimètres.
 */
uint16_t LIDARService::getSigmaMm(void)
{
  return this->results.sigma_mm;
}
