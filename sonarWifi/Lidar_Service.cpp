#include "Lidar_Service.h"





LIDARService::LIDARService():sensor_vl53l4cd_sat(&Wire, D0)
{
}
void LIDARService::findI2C(){
Serial.println();
  Serial.println("Start I2C scanner ...");
  Serial.print("\r\n");
  byte count = 0;
  
  
  for (byte i = 8; i < 120; i++)
  {
    Wire.beginTransmission(i);
    if (Wire.endTransmission() == 0)
      {
      Serial.print("Found I2C Device: ");
      Serial.print(" (0x");
      Serial.print(i, HEX);
      Serial.println(")");
      count++;
      delay(1);
      }
  }
  Serial.print("\r\n");
  Serial.println("Finish I2C scanner");
  Serial.print("Found ");
  Serial.print(count, HEX);
  Serial.println(" Device(s).");
}
void LIDARService::setup()
{
  // Initialize I2C bus.
  Wire.begin();
  this->findI2C();
  


  // Configure VL53L4CD satellite component.
  this->sensor_vl53l4cd_sat.begin();

  // Switch off VL53L4CD satellite component.
  this->sensor_vl53l4cd_sat.VL53L4CD_Off();

  //Initialize VL53L4CD satellite component.
  this->sensor_vl53l4cd_sat.InitSensor();

  // Program the highest possible TimingBudget, without enabling the
  // low power mode. This should give the best accuracy
  this->sensor_vl53l4cd_sat.VL53L4CD_SetRangeTiming(200, 0);

  // Start Measurements
  this->sensor_vl53l4cd_sat.VL53L4CD_StartRanging();
}




void LIDARService::measure()
{
  uint8_t NewDataReady = 0;
  uint8_t status;
  

  do {
    status = this->sensor_vl53l4cd_sat.VL53L4CD_CheckForDataReady(&NewDataReady);
  } while (!NewDataReady);

  if ((!status) && (NewDataReady != 0)) {
    // (Mandatory) Clear HW interrupt to restart measurements
    this->sensor_vl53l4cd_sat.VL53L4CD_ClearInterrupt();

    // Read measured distance. RangeStatus = 0 means valid data
    this->sensor_vl53l4cd_sat.VL53L4CD_GetResult(&(this->results));
  }
}

uint16_t LIDARService::getDistance(void){
  uint16_t distance_mm = this->results.distance_mm - 21;
  results.distance_mm = (results.distance_mm  > 0) ? results.distance_mm :0;
  this->results.distance_mm = (results.distance_mm  > 2000) ? results.distance_mm :-1;
  return results.distance_mm;
}
uint8_t LIDARService::getRangeStatus(void){
  return this->results.range_status;
}
uint16_t LIDARService::getAmbientRatePerSpadKcps(void){
  return this->results.ambient_per_spad_kcps;
}

uint16_t LIDARService::getAmbientRateKcps(void){
  return this->results.ambient_rate_kcps;
}
uint16_t LIDARService::getSignalRateKcps(void){
  return this->results.signal_rate_kcps;
}
uint16_t LIDARService::getSignalRatePerSpadKcps(void){
  return this->results.signal_per_spad_kcps;
}
uint16_t LIDARService::getNumberOfSpad(void){
  return this->results.number_of_spad;
}
uint16_t LIDARService::getSigmaMm(void){
  return this->results.sigma_mm;
}
