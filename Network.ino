#include "Network.h"
char* vTopic = "focusClock/";
WiFiClient ethClient;
PubSubClient client(ethClient);

// time variable
int vFlagTimeSet = 0, vFlagAlarm = 0, vFlagCircle = 0; 
int vHourSet, vMiSet, vHourAlarm, vMiAlarm, vCircle;

// suport function
void pln(String str){
  if(DEBUG){
    String str1 = String(millis()) + ": " + str;
    Serial.println(str1);    
  }
}
void p(String str){
  if(DEBUG){
    Serial.print(str);
  }
}
void p(char wd){
  if(DEBUG){
    Serial.print(wd);
  }
}

int rp(uint8_t a){
  return digitalRead(a);
}

/* s3 */ void hp(uint8_t a){
  digitalWrite(a, LOW);
}
/* s4 */ void lp(uint8_t a){
  digitalWrite(a, HIGH);
}

/* s5 */ void tp(uint8_t a){
  digitalWrite(a, digitalRead(a) ^ 0x01);
}
void beginSmart(){
  WiFi.beginSmartConfig();
  while(1){
           delay(100);
           tp(LED);
           //Kiểm tra kết nối thành công in thông báo
           if(WiFi.smartConfigDone()){
             pln("SmartConfig Success");
             break;
           }
       }
       return;
}

void wifiInit(){
  int cnt = 0;
  pln("Connecting to Wifi");
  WiFi.mode(WIFI_STA);
  delay(1000);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    tp(LED);
    p(".");
    if(cnt++ >= 30){
       beginSmart();
     }
  }
  pln("Connected, IP address: " + WiFi.localIP());
}


// mqtt Init
void mqttInit(){
  client.setServer(mqtt_server, mqtt_port); 
  client.setCallback(callback);
  reconnect();
}

void mqttLoop(){
  if (!client.connected()) {
    Serial.println("hello");
    reconnect();
  }
  client.loop();
}
// time Set
int timeSetAvailable(){
  if(vFlagTimeSet){
    vFlagTimeSet = 0;
    return 1;
  }
  else{
    return 0;
  }
}

int hourSetRead(){
  return vHourSet;
}
int minuteSetRead(){
  return vMiSet;
}

// alarm Set
int alarmAvailable(){
  if(vFlagAlarm){
    vFlagAlarm = 0;
    return 1;
  }
  else{
    return 0;
  }
}

int alarmHourRead(){
  return vHourAlarm;
}
int alarmMinuteRead(){
  return vMiAlarm;
}

// circle Set
int circleAvailable(){
  if(vFlagCircle){
    vFlagCircle = 0;
    return 1;
  }
  else{
    return 0;
  }
}

int circleRead(){
  return vCircle;
}






// mqtt superior
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    pln("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("arduinoClient")) {
      pln("connected");
      // Once connected, publish an announcement...
      //client.publish("outTopic","hello world"); 
      // ... and resubscribe
      client.subscribe(vTopic);
    } else {
      pln("failed, rc=");
      pln(String(client.state()));
      pln(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


void callback(char* topic, byte* payload, unsigned int length) {
  p("Message arrived [" + String(topic) +"] ");
  for (int i = 0; i < length; i++) {
    //gSdt (char)payload[i];
    p((char)payload[i]);
  }
  p('\n');
  DynamicJsonBuffer jsonBuffer(200);
  JsonObject& root = jsonBuffer.parseObject(payload);

  // Test if parsing succeeds.
  if (!root.success()) {
    pln("parseObject() failed");
    //return;
  }
  else{
    if((root["h"] != "") && (root["m"] != "")){
      pln("Set time");
      vHourSet = root["h"];
      vMiSet = root["m"];
      vFlagTimeSet = 1;
    }
    if((root["hA"] != "") && (root["mA"] != "")){
      pln("Set Alarm");
      vHourAlarm = root["hA"];
      vMiAlarm = root["mA"];
      vFlagAlarm = 1;
    }
    if(root["c"] != ""){
      pln("Set Circle ");
      vCircle = root["c"]; 
      vFlagCircle = 1;        
    }
  }
}







