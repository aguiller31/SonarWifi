#ifndef LIDAR_SERVICE
#define LIDAR_SERVICE
//https://github.com/stm32duino/VL53L4CD/tree/main
#include <Arduino.h>
#include <Wire.h>
#include "vl53l4cd_class.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>

//VL53L4CDA
class LIDARService {
  public:
    LIDARService();
    void setup();
    void measure();
    uint16_t getDistance(void);
    uint8_t getRangeStatus(void);
    uint16_t getAmbientRatePerSpadKcps(void);
    uint16_t getAmbientRateKcps(void);
    uint16_t getSignalRateKcps(void);
    uint16_t getSignalRatePerSpadKcps(void);
    uint16_t getNumberOfSpad(void);
    uint16_t getSigmaMm(void);
  private:
    void findI2C(void);
    VL53L4CD_Result_t results;
    VL53L4CD sensor_vl53l4cd_sat;
};

#endif