/*********************************************************************
 * @file  Motor_Service.h
 * @author Guillermin Antoine et Paul Gadanho
 * @brief Définition de la classe MotorService.
 *********************************************************************/

#ifndef MOTOR_SERVICE
#define MOTOR_SERVICE

#include <Arduino.h>
#include <vector>

#define MOTOR_PIN_1 D5
#define MOTOR_PIN_2 D6
#define MOTOR_PIN_3 D7
#define MOTOR_PIN_4 D0

#define MOTOR_STEPS_PER_REV 4096

/**
  * @class MotorService
  * @brief Classe MotorService Permet la rotation du moteur
*/  
class MotorService{
  public:
    /**
     * @brief Constructeur par défaut de la classe MotorService.
     */
    MotorService(void);

    /**
     * @brief Constructeur de la classe MotorService avec délai personnalisé.
     * @param d Le délai entre les étapes du moteur.
     */
    MotorService(int);

    /**
     * @brief Destructeur de la classe MotorService.
     */
    ~MotorService(void);

    /**
     * @brief Initialise les broches du moteur en tant que sorties.
     */
    void setup(void);

    /**
     * @brief Effectue une étape du moteur et met à jour l'angle actuel.
     * @return L'angle actuel après l'étape. Retourne -1 si l'angle n'a pas augmenté.
     */
    int step(void);

    /**
     * @brief Calcule l'angle actuel en fonction du nombre total d'étapes effectuées.
     */
    void calculateCurrentAngle(void);

    /**
     * @brief Obtient l'angle actuel.
     * @return L'angle actuel.
     */
    int getCurrentAngle(void);

    /**
     * @brief Définit l'angle précédent à une valeur spécifiée.
     * @param angle L'angle précédent à définir.
     */
    void setPreviousAngle(int);

    /**
     * @brief Obtient l'angle précédent.
     * @return L'angle précédent.
     */
    int getPreviousAngle(void);

    /**
     * @brief Configure les broches du moteur en fonction de l'étape spécifiée.
     * @param step L'index de l'étape actuelle.
     */
    void setStep(int);

    /**
     * @brief Définit le délai entre les étapes du moteur.
     * @param d Le nouveau délai à définir.
     */
    void setDelay(int);

    /**
     * @brief Obtient le délai entre les étapes du moteur.
     * @return Le délai entre les étapes du moteur.
     */
    int getDelay(void);

  private:
    int delayTime; ///< Le délai entre les étapes du moteur.
    int stepCounter; ///< Le compteur d'étapes du moteur.
    int previousAngle; ///< L'angle précédent du moteur.
    int currentAngle; ///< L'angle actuel du moteur.
};

#endif
