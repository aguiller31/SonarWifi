#ifndef MOTOR_SERVICE
#define MOTOR_SERVICE
#include <Arduino.h>
#define MOTOR_PIN_1 D5  // Remplacez ces valeurs par les broches appropriées
#define MOTOR_PIN_2 D6
#define MOTOR_PIN_3 D7
#define MOTOR_PIN_4 D8

#define MOTOR_STEPS_PER_REV 4096
class MotorService{
  public:
    MotorService(void);
    MotorService(int);
    void setup(void);
    void start(void);
    float getAngle(void);
    void setStep(int);
    void setDelay(int);
    
  private:
    int delayTime;
    int stepCounter;
};
#endif