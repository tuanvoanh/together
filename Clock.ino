#define GETDATA 1
#define UPDATEDATA 2
#define SPEAKERSET 3
#define DISPLAY 4


#include "Cds1307.h"
#include "Network.h"
#include "speaker.h"
#include "led7_595.h"
int gHourAlarm=0,gMinAlarm=0,gPeriodTime=0;
int state=0;


void setup() {
  //Setup Pinout 
  pinMode(SPEAKER_PIN, OUTPUT);
  pinMode(DATACLOCK_PIN, OUTPUT);
  pinMode(STORAGECLOCK_PIN,OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  
  initDS1307();
  set_time(0,0,0);
  wifiInit();
  mqttInit();
}

void getData()
{
  gHour=readDS1307_hour();
  gMin =readDS1307_min();
}

void updateData()
{
  mqttLoop();
  //update time and push to ds1307
  if (timeSetAvailable()) set_time(hourSetRead(),minuteSetRead,0);
  //get alarm
  if (alarmAvailable()) 
  {
    gAlarmHour=alarmHouread();
    gAlarmMin =alarmMinutread();
  }
  //get period
  if (circleAvailable()) 
    gPeriodTime=circleRead();
}
void speakerSet()
{
  checkAlarm(gAlarmHour,gAlarmMin,gHour,gMin);
  setPeriod(gPeriodTime);
  outputAlarm();
}
void loop() {
  switch (state)
  {
    case GETDATA:
    {
            getData();
            state++;
            break;
    }
    case UPDATEDATA:
    {
            updateData();
            state++;
            break;
    }
    case SPEAKERSET:
    {
            speakerSet();
            state++;
            break;
    }
    case DISPLAY:
    {
            ledDisplay(gHour,gMin);
            state=1;
            break;
    }
    default:
            {}
  }
}
