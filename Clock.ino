#include "Cds1307.h"
#include "Network.h"
#include "speaker.h"
#include "led7_595.h"
//#include "Tspeaker.h"

unsigned long vTime=0;
uint8_t gHour=0,gMin=0;
uint8_t speaker=0;
uint8_t a = 1;

void upTime()
{
  gHour+= (uint8_t)((++gMin)/60);
  gMin=gMin%60;
  gHour=gHour%24;
}

 
void getData()
{
  gHour=readDS1307_hour();
  gMin =readDS1307_min();
  
  vTime=millis();
}
uint8_t wifiAvai()
{
  return ((timeSetAvailable())||(alarmAvailable())||(circleAvailable()));
}
void updateData()
{
  
  //get,update time and push to ds1307
  if (timeSetAvailable())
  {
    Serial.print("Hour: ");
    Serial.println(hourSetRead());
    Serial.print("minute: ");
    Serial.println(minuteSetRead());
    set_time(hourSetRead(),minuteSetRead(),0);
    getData();
  }
  //get and update alarm
  if (alarmAvailable()) 
  {
    Serial.print("Hour alarm: ");
    Serial.println(alarmHourRead());
    Serial.print("minute alarm: ");
    Serial.println(alarmMinuteRead());
    alarmUpdate(alarmHourRead(),alarmMinuteRead());
  } 
  //get and update period
  if (circleAvailable())
  {
    periodUpdate(circleRead(),gHour,gMin);
    Serial.print("Circle: ");
    Serial.println(circleRead());
  }
}
void setup() {
  //Setup Pinout 
  Serial.begin(9600);
  speakerInit();
  ledInit();
  pinMode(LED,OUTPUT);
  
  initDS1307();
//  set_time(13,47,0);
  wifiInit();
  mqttInit();
  //state=1;
  
}


void loop() {  
  mqttLoop();
  //IDLE STATE
  //display time to LED + mqttLoop
  //it make sure the that the 7seg led display is operating good
  //mqttLoop make sure data is received
  ledDisplay(gHour,gMin);
//  updateData();
  //mqttLoop();  
//  Serial.print(gHour);
//  Serial.print(":");
//  Serial.println(gMin);
  //TIME CHECK STATE
  //count up minute after 60sec = 1min
  //After 1 min, if on alarm time or on period time then set speaker
  if ( abs(millis()-vTime)>=60000 ) 
  {
    Serial.println("vTime");
    upTime();
    vTime=millis();
    if (speakerAvai(gHour,gMin)) 
    {
      speaker=1;
      Serial.println("alarm");
    }
  }

  //GET WIFI STATE
  //If wifi data available, get data and update
  //if (wifiAvai()) 
  updateData();
  //if speaker set(mean that on alarm time or on period time then send sound
  //it's auto off when end of time
  if (speaker==1) 
  {
    Serial.print("speakerout: ");
    Serial.println(digitalRead(13));
    speaker=speakerOutput();
  }

  //GET DS1307 STATE
  //After 10 min, get back data from DS1307 to make sure that time is correct
  if ((gMin%10==0))
    getData();
}
