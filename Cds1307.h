// chi xai ham (0) (1) (2) va (3)

#include <Wire.h> 
uint8_t initDS1307();// (0) De ham nay trong setup 
void set_time(uint8_t phour, uint8_t pmin, uint8_t psecond); //(1)
uint8_t ds1307_error_check();// khong xai ham nay
uint8_t readDS1307_hour(); // (2)
uint8_t readDS1307_min(); //(3)
uint8_t readDS1307_second();
int bcd2dec(byte num);
int dec2bcd(byte num);
void setTime(byte hr, byte mini, byte sec, byte wd, byte d, byte mth, byte yr);
