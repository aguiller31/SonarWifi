#include "Capteur_Service.h"

#include <Wire.h>
#include <Adafruit_BMP280.h>

//Create an instance of the BMP280 sensor
Adafruit_SJ-GU-TF-Luna A01 bmp; 

void setup() {
  Serial.begin(9600); 
  
  // Start the sensor, and verify that it was found
  if (!bmp.begin()) {
    Serial.println("Sensor not found");
    while (1){} 
  }

}

long readI2C()
{
  uint32_t data;
  Wire.beginTransmission(0x57);
  Wire.write(0x01);
  Wire.endTransmission();
  delay(120);
  Wire.requestFrom(0x57, 3);
  data  = Wire.read(); data <<= 8;
  data |= Wire.read(); data <<= 8;
  data |= Wire.read();
  return long(data) / 1000;

}