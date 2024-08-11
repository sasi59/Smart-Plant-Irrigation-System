#include <LiquidCrystal_I2C.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
 
char auth[] = "uBTcT8j6LZTNPvcxkRg9Y";
char ssid[] = "JDE";
char pass[] = "par12345";
 
BlynkTimer timer;
bool Relay = 0;
 
DHT dht(D3, DHT22);
#define sensor A0
#define waterPump D5
 
void setup() {
  Serial.begin(9600);
  pinMode(waterPump, OUTPUT);
  digitalWrite(waterPump, HIGH);
  lcd.begin();
  lcd.backlight();
  dht.begin();
 
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
 
  lcd.setCursor(1, 0);
  lcd.print("System Loading");
  for (int a = 0; a <= 15; a++) {
    lcd.setCursor(a, 1);
    lcd.print(".");
    delay(500);
  }
  lcd.clear();
 
  timer.setInterval(100L, DHT22sensor);
  timer.setInterval(100L, soilMoistureSensor);
}
 
//Get the button value
BLYNK_WRITE(V7) {
  Relay = param.asInt();
 
  if (Relay == 1) {
    digitalWrite(waterPump, LOW);
 
  } else {