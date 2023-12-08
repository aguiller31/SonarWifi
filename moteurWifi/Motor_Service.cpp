/*********************************************************************
 * @file  Motor_Service.cpp
 * @author Guillermin Antoine et Paul Gadanho
 * @brief Implémentation de la classe MotorService.
 *********************************************************************/

#include "Motor_Service.h"
#include <vector>

const std::vector<std::vector<int>> steps = {
    {1, 0, 0, 1},
    {1, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 1},
    {0, 0, 0, 1}
};

/**
 * @brief Constructeur par défaut de la classe MotorService.
 */
MotorService::MotorService(void) : delayTime(5), stepCounter(0), previousAngle(0) {}

/**
 * @brief Constructeur de la classe MotorService avec délai personnalisé.
 * @param d Le délai entre les étapes du moteur.
 */
MotorService::MotorService(int d) : delayTime(d), stepCounter(0), previousAngle(0) {}

/**
 * @brief Destructeur de la classe MotorService.
 */
MotorService::~MotorService() {
    Serial.println("La classe Moteur a été détruite");
}

/**
 * @brief Configure les broches du moteur en fonction de l'étape spécifiée.
 * @param step L'index de l'étape actuelle.
 */
void MotorService::setStep(int step) {
    digitalWrite(MOTOR_PIN_1, steps[step][0]);
    digitalWrite(MOTOR_PIN_2, steps[step][1]);
    digitalWrite(MOTOR_PIN_3, steps[step][2]);
    digitalWrite(MOTOR_PIN_4, steps[step][3]);
}

/**
 * @brief Effectue une étape du moteur et met à jour l'angle actuel.
 * @return L'angle actuel après l'étape. Retourne -1 si l'angle n'a pas augmenté.
 */
int MotorService::step(void) {
    for (auto it = steps.begin(); it != steps.end(); ++it) {
        this->setStep(it - steps.begin());
        delay(this->delayTime);
        this->stepCounter++;
    }
    this->calculateCurrentAngle();
    if (this->currentAngle != this->previousAngle) {
        this->previousAngle = this->currentAngle;
        return this->currentAngle;
    }
    return -1; // Si l'angle n'a pas augmenté.
}

/**
 * @brief Calcule l'angle actuel en fonction du nombre total d'étapes effectuées.
 */
void MotorService::calculateCurrentAngle(void)
{
    this->currentAngle = (this->stepCounter % MOTOR_STEPS_PER_REV) * (360.0 / MOTOR_STEPS_PER_REV);
}

/**
 * @brief Définit l'angle précédent à une valeur spécifiée.
 * @param angle L'angle précédent à définir.
 */
void MotorService::setPreviousAngle(int angle) {
    this->previousAngle = angle;
}

/**
 * @brief Obtient l'angle précédent.
 * @return L'angle précédent.
 */
int MotorService::getPreviousAngle(void) {
    return this->previousAngle;
}

/**
 * @brief Obtient l'angle actuel.
 * @return L'angle actuel.
 */
int MotorService::getCurrentAngle(void) {
    return currentAngle;
}

/**
 * @brief Définit le délai entre les étapes du moteur.
 * @param d Le nouveau délai à définir.
 */
void MotorService::setDelay(int d) {
    this->delayTime = d;
}

/**
 * @brief Obtient le délai entre les étapes du moteur.
 * @return Le délai entre les étapes du moteur.
 */
int MotorService::getDelay(void) {
    return this->delayTime;
}

/**
 * @brief Initialise les broches du moteur en tant que sorties.
 */
void MotorService::setup(void)
{
    pinMode(MOTOR_PIN_1, OUTPUT);
    pinMode(MOTOR_PIN_2, OUTPUT);
    pinMode(MOTOR_PIN_3, OUTPUT);
    pinMode(MOTOR_PIN_4, OUTPUT);
}
