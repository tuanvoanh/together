#ifndef __led7_595_h__
#define __led7_595_h__

#include "stdint.h"

#define DATACLOCK_PIN 14 //DH_CP PIN IN 74HC595 (PIN14)
#define STORAGECLOCK_PIN 16 //ST_CP PIN IN 74HC595 (PIN12)
#define DATA_PIN 0 // DS PIN IN 54HC595 (PIN11)

#define SCAN 1 //delay time after display 1 digic

//extern uint8_t gLED[10];
//extern uint8_t gDigit[4];

extern void dataSend(uint8_t vData);
extern void dataLatch(uint8_t vData);
extern void ledDisplay(uint8_t vHour, uint8_t vMin);//use this in loop funtion to export data to LED7Seg
//vHour,vMin: time to display
void displayInit();
#endif
