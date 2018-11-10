#include "Cds1307.h"
void setup()
{
  initDS1307();
  Serial.begin(9600);
}
void loop()
{
  Serial.print("hour: ");
  Serial.println(readDS1307_hour());
  Serial.print("min: ");
  Serial.println(readDS1307_min());
  delay(1000);
}
  
