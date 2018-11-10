#include "Cds1307.h"
//#define ERRORRR 100
#define LED_STATUS 13
/* Địa chỉ của DS1307 */
const byte DS1307 = 0x68;
/* Số byte dữ liệu sẽ đọc từ DS1307 */
const byte NumberOfFields = 7;
 
/* khai báo các biến thời gian */
uint8_t second, minute, hour, day, wday, month, year;

uint8_t initDS1307()
{
  pinMode(LED_STATUS,OUTPUT);
  Wire.begin(); // khoi dong I2C
}

void set_time(uint8_t phour, uint8_t pmin, uint8_t psecond)
{
   setTime(phour, pmin, psecond, 1, 8, 2, 15);
}
//void loop()
//{
//  Serial.print("hour: ");
//  Serial.println(readDS1307_hour());
//  Serial.print("min: ");
//  Serial.println(readDS1307_min());
//  delay(1000);
//}

uint8_t ds1307_error_check()
{
//  uint8_t vfirst,vsecond;
//  vfirst = readDS1307_second();
//  delay(1200);
//  vsecond = readDS1307_second();
//  if(vfirst == vsecond)
//    {
//      digitalWrite(LED_STATUS,HIGH);
//      return 0;
//    }
//  else 
//  {
//    Wire.endTransmission();
//    digitalWrite(LED_STATUS,LOW);
    return 1;
  //}
}

uint8_t readDS1307_hour()
{
        if(!ds1307_error_check())
        {
          Serial.println("error in READ");
          //set_time(hour,minute,second);
//          return ERRORR;
        }
        Wire.beginTransmission(DS1307);
        Wire.write((byte)0x00);
        Wire.endTransmission();
        Wire.requestFrom(DS1307, NumberOfFields);
        second = bcd2dec(Wire.read() & 0x7f);
        minute = bcd2dec(Wire.read() );
        hour   = bcd2dec(Wire.read() & 0x3f); // chế độ 24h.
        return hour;
}

uint8_t readDS1307_min()
{
     if(!ds1307_error_check())
        {
          Serial.println("error in READ");
          //set_time(hour,minute,second);
          //return ERRORR;
        }
     Wire.beginTransmission(DS1307);
     Wire.write((byte)0x00);
     Wire.endTransmission();
     Wire.requestFrom(DS1307, NumberOfFields);
     second = bcd2dec(Wire.read() & 0x7f);
     minute = bcd2dec(Wire.read() );
     hour   = bcd2dec(Wire.read() & 0x3f); // chế độ 24h. 
     return minute;
}

uint8_t readDS1307_second()
{
     digitalWrite(LED_STATUS,HIGH);
     Wire.beginTransmission(DS1307);
     Wire.write((byte)0x00);
     Wire.endTransmission();
     Wire.requestFrom(DS1307, NumberOfFields);
     second = bcd2dec(Wire.read() & 0x7f);
     minute = bcd2dec(Wire.read() );
     hour   = bcd2dec(Wire.read() & 0x3f); // chế độ 24h.
     digitalWrite(LED_STATUS,LOW);
     return second;
}
/* Chuyển từ format BCD (Binary-Coded Decimal) sang Decimal */
int bcd2dec(byte num)
{
        return ((num/16 * 10) + (num % 16));
}
/* Chuyển từ Decimal sang BCD */
int dec2bcd(byte num)
{
        return ((num/10 * 16) + (num % 10));
}
 
/* cài đặt thời gian cho DS1307 */
void setTime(byte hr, byte mini, byte sec, byte wd, byte d, byte mth, byte yr)
{
        if(!ds1307_error_check())
        {
          Serial.println("error in READ");
          //set_time(hour,minute,second);
          digitalWrite(LED_STATUS,HIGH);
          //return ERRORR;
        }
        Wire.beginTransmission(DS1307);
        Wire.write(byte(0x00)); // đặt lại pointer
        Wire.write(dec2bcd(sec));
        Wire.write(dec2bcd(mini));
        Wire.write(dec2bcd(hr));
        Wire.write(dec2bcd(wd)); // day of week: Sunday = 1, Saturday = 7
        Wire.write(dec2bcd(d)); 
        Wire.write(dec2bcd(mth));
        Wire.write(dec2bcd(yr));
        Wire.endTransmission();
        digitalWrite(LED_STATUS,LOW);
}

