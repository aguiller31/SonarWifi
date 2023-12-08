#include "Motor_Service.h"



// Définir le tableau de séquences de pas pour le moteur 28BYJ-48
const int steps[][4] = {
    {1, 0, 0, 1},
    {1, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 1},
    {0, 0, 0, 1}
};

void MotorService::setStep(int step) {
    digitalWrite(MOTOR_PIN_1, steps[step][0]);
    digitalWrite(MOTOR_PIN_2, steps[step][1]);
    digitalWrite(MOTOR_PIN_3, steps[step][2]);
    digitalWrite(MOTOR_PIN_4, steps[step][3]);
}


MotorService::MotorService(void)
{
    this->delayTime = 5;
    this->stepCounter =0;
}
MotorService::MotorService(int d)
{
    this->delayTime = d;
    this->stepCounter =0;
}
void MotorService::setDelay(int d)
{
    this->delayTime = d;
}
void MotorService::setup(void)
{
   
    pinMode(MOTOR_PIN_1, OUTPUT);
    pinMode(MOTOR_PIN_2, OUTPUT);
    pinMode(MOTOR_PIN_3, OUTPUT);
    pinMode(MOTOR_PIN_4, OUTPUT);
}

void MotorService::start(void)
{
   for (int i = 0; i < 8; ++i) {
            this->setStep(i);
            delay(this->delayTime);
            this->stepCounter++;
        }
}
 
float MotorService::getAngle(void)
{
  return (this->stepCounter % MOTOR_STEPS_PER_REV) * (360.0 / MOTOR_STEPS_PER_REV);
}