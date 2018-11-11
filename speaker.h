#ifndef __SPEAKER_H__
#define __SPEAKER_H__



#define SPEAKER_PIN 13


#define ALARM 70
#define PERIOD 500


void speakerInit();

void periodUpdate(uint8_t pPeriod,uint8_t pHour,uint8_t pMin);
void alarmUpdate(uint8_t pHour, uint8_t pMin);

uint8_t speakerAvai(uint8_t pHour,uint8_t pMin);//Check alarm after 1 min
uint8_t speakerOutput();// If speakerAvai, run this until it return 0;



#endif
