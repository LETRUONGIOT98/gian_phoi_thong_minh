
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo gianphoi;

Servo maiche;
#include <Adafruit_Sensor.h>
#include <DHT.h>
int mogianphoi = 0;
int donggianphoi = 180;
int momaiche = 0;
int dongmaiche = 180;
float t,h;
#include "DHT.h"

#define DHTPIN 2

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
char auth[] = "mFmi74_v6VowGqAoAtLx4uhYIQUJUhUA";  //Không thay đổi mã này
char ssid[] = "Thu Thao";          //Tên Wifi
char pass[] = "917664ab";          //Mật khẩu wifi
DHT dht(DHTPIN, DHTTYPE);
#define den 13
#define quat 27
#define BT1 26
#define BT2 25
#define BT3 33
#define BT4 32
#define BT5 35
#define cambienmua 18
#define as 19
#define hanhtrinhtrong 34
#define hanhtrinhngoai 39
#define GPT 12
#define GPN 14
int dkquat,dkden,dkmai,dkgianphoi,tudong = 1,i=0,j=0;
long times;
BLYNK_WRITE(V0) //Kênh điều khiển bật tắt thiết bị
{ 
  dkquat = param.asInt();
  digitalWrite(quat, dkquat);
  Blynk.virtualWrite(V6, 0);
  tudong =0;
}

BLYNK_WRITE(V1) //Kênh điều khiển bật tắt thiết bị
{ 
  dkden = param.asInt();
  digitalWrite(den, dkden);
  Blynk.virtualWrite(V6, 0);
  tudong =0;
}
BLYNK_WRITE(V2) //Kênh điều khiển bật tắt thiết bị
{ 
  dkmai = param.asInt();
  maiche.write(dkmai);  
  Blynk.virtualWrite(V6, 0);
  tudong =0;
}
BLYNK_WRITE(V3) //Kênh điều khiển bật tắt thiết bị
{ 
  dkgianphoi = param.asInt();
   gianphoi.write(dkgianphoi);
  Blynk.virtualWrite(V6, 0);
  tudong =0;
}
BLYNK_WRITE(V6) //Kênh điều khiển bật tắt thiết bị
{ 
  tudong = param.asInt();
}
void setup()
{   gianphoi.attach(23);           //Chân điều khiển servo gianphoi là D25
    maiche.attach(15);                 //Chân điều khiển servo mái che là D26
    gianphoi.write(90);
    maiche.write(90);   
    Wire.begin();
    pinMode(cambienmua, INPUT_PULLUP);
    pinMode(BT1, INPUT_PULLUP); 
    pinMode(BT2, INPUT_PULLUP); 
    pinMode(BT3, INPUT_PULLUP); 
    pinMode(BT4, INPUT_PULLUP); 
    pinMode(BT5, INPUT_PULLUP); 
    pinMode(as, INPUT_PULLUP); 
    pinMode(hanhtrinhtrong, INPUT_PULLUP); 
    pinMode(hanhtrinhngoai, INPUT_PULLUP); 
    pinMode(GPT, INPUT_PULLUP); 
    pinMode(GPN, INPUT_PULLUP); 
    pinMode(den, OUTPUT);
    pinMode(quat, OUTPUT);
    digitalWrite(den, HIGH);
    digitalWrite(quat, HIGH);
     Serial.begin(9600);
    pinMode(den, OUTPUT);
    Blynk.begin(auth, ssid, pass,"blynk-server.com",8080);
    dht.begin();
    lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
    Serial.println("DA KHOI DONG XONG");
}
void loop(){
  Blynk.run();
  if(millis()-times > 2000){
    float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  Serial.print("NHIET DO:  "); Serial.print(t);
  Serial.print("   DO AM:  "); Serial.print(h);
  Serial.println();
  times = millis();
Blynk.virtualWrite(V4, t);
Blynk.virtualWrite(V5, h);
lcd.setCursor(0, 0);       //Đưa con trỏ màn hình về vị trí số 0 hàng 0
  lcd.print("T:     C H:    %"); 
  lcd.setCursor(2, 0);
  lcd.print(t);                //Ghi giá trị nhiệt độ lên màn hình
  lcd.setCursor(11, 0);
  lcd.print(h);            //Ghi giá trị độ ẩm lên màn hình
  }
 if(digitalRead(BT1) == 0){
  Serial.println("NHAN NUT 1");
  tudong = 1;
  Blynk.virtualWrite(V6, tudong);
  delay(500);
 }
 //////Chế độ Tự động);//////////
if(tudong == 1){
 lcd.setCursor(0, 1);
  lcd.print("    TU DONG     "); 
  if(digitalRead(cambienmua) == 0 && digitalRead(hanhtrinhtrong) == 1){
    maiche.write(dongmaiche);
    Blynk.virtualWrite(V2, dongmaiche);
  }
  if(digitalRead(cambienmua) == 0 && digitalRead(hanhtrinhtrong) == 0){
    maiche.write(90);
    Blynk.virtualWrite(V2, 90);
  }
  if(digitalRead(cambienmua) == 1 && digitalRead(hanhtrinhngoai) == 1){
    maiche.write(momaiche);
    Blynk.virtualWrite(V2, momaiche);
  }
  if(digitalRead(cambienmua) == 1 && digitalRead(hanhtrinhngoai) == 0){
    maiche.write(90);
    Blynk.virtualWrite(V2, 90);
  }


  ///////
  if(digitalRead(cambienmua) == 0 && digitalRead(GPT) == 1){
    gianphoi.write(donggianphoi);
    Blynk.virtualWrite(V3, donggianphoi);
  }
  if(digitalRead(cambienmua) == 0 && digitalRead(GPT) == 0){
    gianphoi.write(90);
    Blynk.virtualWrite(V3, 90);
  }
  if(digitalRead(cambienmua) == 1 && digitalRead(GPN) == 1){
    gianphoi.write(mogianphoi);
    Blynk.virtualWrite(V3, mogianphoi);
  }
  if(digitalRead(cambienmua) == 1 && digitalRead(GPN) == 0){
    gianphoi.write(90);
    Blynk.virtualWrite(V3, 90);
  }
  if(digitalRead(as) == 1 || digitalRead(cambienmua) == 0){
    digitalWrite(den, LOW);
    Blynk.virtualWrite(V1, 0);}
    else{digitalWrite(den, HIGH);
    Blynk.virtualWrite(V1, 1); 
  }
  if(h > 90 ||digitalRead(cambienmua) == 0){
    digitalWrite(quat, LOW);
    Blynk.virtualWrite(V0, 0);
  }
  else{digitalWrite(quat, HIGH);
  Blynk.virtualWrite(V0, 1);
  }
}
else{lcd.setCursor(0, 1);
  lcd.print("    THU CONG    "); }
//////////Chế độ Thủ công/////////////////////////
if(digitalRead(BT2) == 0){
  tudong =0;
  if(tudong == 0){
  Serial.println("NHAN NUT 2");
  digitalWrite(den, !digitalRead(den));
    Blynk.virtualWrite(V1, digitalRead(den));
    Blynk.virtualWrite(V6, 0);
  
    delay(500);
  }
}
if(digitalRead(BT3) == 0){
  
  Serial.println("NHAN NUT 3");
  tudong =0;
  if(tudong == 0){
  digitalWrite(quat, !digitalRead(quat));
    Blynk.virtualWrite(V0, digitalRead(quat));
    Blynk.virtualWrite(V6, 0);
    delay(500);
}}
if(digitalRead(BT4) == 0){
  Serial.println("NHAN NUT 4");
  tudong =0;
  if(tudong == 0){
  Blynk.virtualWrite(V6, 0);
  i = i+1;
  delay(500);
  if(i > 1)i=0;}}

  if(tudong == 0){
  if(i == 0 && digitalRead(hanhtrinhtrong) == 1){ 
    maiche.write(dongmaiche);
    Blynk.virtualWrite(V2, dongmaiche);
  }
  if(i == 0 && digitalRead(hanhtrinhtrong) == 0){ 
    maiche.write(90);}
    
  if(i == 1 && digitalRead(hanhtrinhngoai) == 1){ 
    maiche.write(momaiche);
    Blynk.virtualWrite(V2, momaiche);
  }
  if(i == 1 && digitalRead(hanhtrinhngoai) == 0){
    maiche.write(90);}
 Serial.println("i: " +String(i));
  }
if(digitalRead(BT5) == 0){
  Serial.println("NHAN NUT 5");
  tudong =0;
  if(tudong == 0){
  Blynk.virtualWrite(V6, 0);
  tudong =0;
  j = j+1;
  delay(500);
  if(j > 1)j=0;}}
 
  if(tudong == 0){
  if(j == 0 && digitalRead(GPT) == 1){ 
    gianphoi.write(donggianphoi);
    Blynk.virtualWrite(V3, donggianphoi);
  }
  if(j == 0 && digitalRead(GPT) == 0){ 
    gianphoi.write(90);}
    
  if(j == 1 && digitalRead(GPN) == 1){ 
    gianphoi.write(mogianphoi);
    Blynk.virtualWrite(V3, mogianphoi);
  }
  if(j == 1 && digitalRead(GPN) == 0){
    gianphoi.write(90);}
 Serial.println("j: " +String(j));
  }
  

}
