#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#define DEBUG 0 // 0 => không hiện serial, 1 => in serial 
#define LED 2
//mqtt define
#include <PubSubClient.h>
//#define mqtt_server "cretatech.com" // Thay bằng thông tin của bạn
#define mqtt_server "192.168.1.222" // Thay bằng thông tin của bạn
#define mqtt_port 1883

// setup wifi
void wifiInit();
//
// setup mqtt
void mqttInit();
void mqttLoop();
//
//// nhung ham Available = 1 khi có thay đổi từ server
//// khi ham Available = 1 thì dùng các hàm Read để lấy về giá trị 
int timeSetAvailable(); // có thay đổi giờ hệ thống 
int hourSetRead(); // lấy giờ mới 
int minuteSetRead(); // lấy phút mới 
 
int alarmAvailable(); //có hẹn giờ mới 
int alarmHourRead();   // lấy giờ hẹn mới 
int alarmMinutRead(); // lấy phút hẹn mới   

int circleAvailable(); // có chu kỳ mới 
int circleRead();      // lấy chu kỳ mới  
