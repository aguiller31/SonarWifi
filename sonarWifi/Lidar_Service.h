/*********************************************************************
 * @file  Lidar_Service.h
 * @author Guillermin Antoine et Paul Gadanho
 * @brief Définition de la classe LIDARService.
 *********************************************************************/

#ifndef LIDAR_SERVICE
#define LIDAR_SERVICE

#include <Arduino.h>
#include <Wire.h>
#include <stdexcept>
#include "vl53l4cd_class.h"

/**
 * @class LIDARService
 * @brief Gère les fonctionnalités du capteur LIDAR VL53L4CD.
 * Cette classe hérite de la classe VL53L4CD pour utiliser ses fonctionnalités.
 */
class LIDARService : public VL53L4CD{
  public:
    /**
     * @brief Constructeur de la classe LIDARService.
     * Initialise le capteur LIDAR VL53L4CD.
     */
    LIDARService();

    /**
     * @brief Configure le capteur LIDAR.
     * Initialise le capteur, le configure et démarre la mesure.
     */
    void setup();

    /**
     * @brief Effectue une mesure avec le capteur LIDAR.
     * Attend la disponibilité des nouvelles données et récupère le résultat.
     * Lance une exception en cas d'échec de la mesure.
     */
    void measure();

    /**
     * @brief Récupère la distance mesurée par le capteur LIDAR.
     * Ajuste la valeur pour assurer qu'elle est dans une plage valide.
     * @return La distance mesurée en millimètres.
     */
    uint16_t getDistance(void);

    /**
     * @brief Récupère le statut de plage du capteur LIDAR.
     * @return Le statut de plage.
     */
    uint8_t getRangeStatus(void);

    /**
     * @brief Récupère le taux ambiant par SPAD du capteur LIDAR.
     * @return Le taux ambiant par SPAD en kilo counts par seconde (kcps).
     */
    uint16_t getAmbientRatePerSpadKcps(void);

    /**
     * @brief Récupère le taux ambiant du capteur LIDAR.
     * @return Le taux ambiant en kilo counts par seconde (kcps).
     */
    uint16_t getAmbientRateKcps(void);

    /**
     * @brief Récupère le taux de signal du capteur LIDAR.
     * @return Le taux de signal en kilo counts par seconde (kcps).
     */
    uint16_t getSignalRateKcps(void);

    /**
     * @brief Récupère le taux de signal par SPAD du capteur LIDAR.
     * @return Le taux de signal par SPAD en kilo counts par seconde (kcps).
     */
    uint16_t getSignalRatePerSpadKcps(void);

    /**
     * @brief Récupère le nombre de SPAD du capteur LIDAR.
     * @return Le nombre de SPAD.
     */
    uint16_t getNumberOfSpad(void);

    /**
     * @brief Récupère l'écart-type en millimètres du capteur LIDAR.
     * @return L'écart-type en millimètres.
     */
    uint16_t getSigmaMm(void);

  private:
    VL53L4CD_Result_t results; ///< Résultats de la mesure du capteur LIDAR.
};

#endif
