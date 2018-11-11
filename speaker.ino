#include "speaker.h"

static uint8_t gAlarmHour=25,gAlarmMin=0,gPeriodHour=25,gPeriodMin=0;
static uint8_t gPeriod=0;
static int gSpeaker=0;

void speakerInit()
{
  pinMode(SPEAKER_PIN,OUTPUT);
}

void speakerToggle()
{
  digitalWrite(SPEAKER_PIN,!digitalRead(SPEAKER_PIN));
  
}
void nextperiodUpdate(uint8_t pHour,uint8_t pMin)
{
  gPeriodHour=pHour+(uint8_t)((pMin+gPeriod)/60);
  gPeriodMin = (pMin+gPeriod)%60; 
  
}
void periodUpdate(uint8_t pPeriod,uint8_t pHour,uint8_t pMin)
{
  gPeriod=pPeriod;
  nextperiodUpdate(pHour,pMin);

}
void alarmUpdate(uint8_t pHour, uint8_t pMin)
{
  gAlarmHour=pHour;
  gAlarmMin = pMin;

}
uint8_t speakerAvai(uint8_t pHour,uint8_t pMin)
{
  
  //Check Alarm
  if ( (pHour==gAlarmHour)&&(pMin==gAlarmMin) )
  {
    gSpeaker=1;
    if ( (pHour==gPeriodHour)&&(pMin==gPeriodMin) )
          nextperiodUpdate(pHour,pMin);
    return 1;   
  }
  //Check period
  if ( (pHour==gPeriodHour)&&(pMin==gPeriodMin) )
  {
    gSpeaker=-4;
    nextperiodUpdate(pHour,pMin);
    return 1;
  }
  return 0;
}
uint8_t speakerOutput()
{
  static unsigned long vTime=0;
  if ((gSpeaker==0)||(gSpeaker==30))//850))
  {
    vTime=0;
    gSpeaker=0;
    digitalWrite(SPEAKER_PIN,0);
    return 0;
    
  } 
  if (gSpeaker<0)
  {    
    if ( (millis()-vTime)>=PERIOD)
    {
        speakerToggle();
        gSpeaker++;
        vTime=millis();
    }
  }
  else if (gSpeaker>0)
  {
    if ( ( (millis()-vTime)>=ALARM) )
    {
        
        gSpeaker++;
        vTime=millis();
        if ((gSpeaker%16)<8)
            speakerToggle();
    }
  }
  return 1;
}
