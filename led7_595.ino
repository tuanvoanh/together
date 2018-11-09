


uint8_t gLED[11]={0x05,0x7D,0x46,0x54,0x3C,0x94,0x84,0x5D,0x04,0x14,0xFF};
uint8_t gDigit[5]={0,1,2,4,8};

void dataSend(uint8_t vData)
{
  for (uint8_t i=0;i<=7;i++)
  {
  
      digitalWrite(DATA_PIN,(vData&(1<<i))>>i);     
      digitalWrite(DATACLOCK_PIN,1);
      digitalWrite(DATACLOCK_PIN,0);
  }
}
void dataLatch(uint8_t vData)
{
  digitalWrite(STORAGECLOCK_PIN,0);
  dataSend(vData);
  digitalWrite(STORAGECLOCK_PIN,1);
  
}

void ledDisplay(uint8_t  vHour, uint8_t  vMin)
{
  static uint8_t digic=4;//Back to last stage
  static unsigned long vTime=SCAN; // Scan for first time 
  if ( (millis()-vTime)>=SCAN )
  {
      dataSend(gDigit[digic]);
      dataLatch(gLED[10]);
      delayMicroseconds(100);
      if (digic==4) digic=1; else digic++;
      dataSend(gDigit[digic]);
      if (digic==1)
                  dataLatch(gLED[vHour/10]);     
      else if (digic==2)
                  dataLatch(gLED[vHour%10]-4);
      else if (digic==3)
                  dataLatch(gLED[vMin/10]);
      else if (digic==4)
                  dataLatch(gLED[vMin%10]);
      vTime=millis();
  }
}
