#include "Network.h"
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  wifiInit();
  mqttInit();
}

void loop() {
  // put your main code here, to run repeatedly:
  mqttLoop();
  if (timeSetAvailable()){
    Serial.print("Set time :");
    Serial.print(hourSetRead());
    Serial.print(":");
    Serial.println(minuteSetRead());
  }
  if (alarmAvailable()){
    Serial.print("Set Alarm :");
    Serial.print(alarmHourRead());
    Serial.print(":");
    Serial.println(alarmMinuteRead());
  }
  if (circleAvailable()){
    Serial.print("Set circle :");
    Serial.print(circleRead());
  } 
}
