#include "WString.h"
#include "Debug_Service.h"

DebugService::DebugService(int baud_rate)
{
  this->baud_rate = baud_rate;
  
  Serial.begin(baud_rate);
}
void DebugService::println(String str)
{
 Serial.println(str);
}
void DebugService::print(String str)
{
 Serial.print(str);
}