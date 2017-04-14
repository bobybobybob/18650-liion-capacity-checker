/* 
* Battery Capacity Checker from Adam Welch
* Little Addons by bobybobybob
* Blink without Delay from https://www.arduino.cc/en/Tutorial/BlinkWithoutDelay 
* Uses LCD 16x2 Display
* Uses 1 Ohm power resister as shunt - Load can be any suitable resister or lamp
* 
* Adam Welch Battery Capacity Checkeroriginal YouTube Video: https://www.youtube.com/embed/qtws6VSIoYk
* 
* http://AdamWelch.Uk
* 
*/
 
#include <Wire.h>  // Comes with Arduino IDE
#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);   // initialize the library with the numbers of the interface pins
 
#define gatePin 11
#define highPin A0
#define lowPin A1
 
boolean finished = false;
int printStart = 0;
int interval = 5000;                  //Interval (ms) between measurements
 
float mAh = 0.0;
float shuntRes = 1.0;                 // In Ohms - Shunt resistor resistance
float voltRef = 4.65;                 // Reference voltage (probe your 5V pin) 
float current = 0.0;
float battVolt = 0.0;
float shuntVolt = 0.0;
float battLow = 2.9;
 
unsigned long previousMillis = 0;
unsigned long millisPassed = 0;
const int ledPin =  LED_BUILTIN;      // the number of the LED pin
int ledState = LOW;                   // ledState used to set the LED
unsigned long previousLEDMillis = 0;  // will store last time LED was updated
const long LEDinterval = 1000;        // interval at which to blink (milliseconds)
 
void setup() {
 pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  Serial.println("Battery Capacity Checker v1.1");
  Serial.println("battVolt   current     mAh");
 
  pinMode(gatePin, OUTPUT);
  digitalWrite(gatePin, LOW);
 
  lcd.begin(16,2);   // initialize the lcd for 16 chars 2 lines, turn on backlight
  //lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Battery Check");
  lcd.setCursor(0,1);
  lcd.print("AdamWelch.Uk");
  delay(2000);
  lcd.clear();
  //lcd.noBacklight();
  }
 
void loop() {
 
  battVolt = analogRead(highPin) * voltRef / 1024.0;
  shuntVolt = analogRead(lowPin) * voltRef / 1024.0;

if (finished == true) {
    unsigned long currentLEDMillis = millis();

  if (currentLEDMillis - previousLEDMillis >= LEDinterval) {
    previousLEDMillis = currentLEDMillis;                           // save the last time you blinked the LED
    if (ledState == LOW) {ledState = HIGH;} else {ledState = LOW;}  // if the LED is off turn it on and vice-versa:
    digitalWrite(ledPin, ledState);                                 // set the LED with the ledState of the variable:
    }}
   
  if(battVolt >= battLow && finished == false)  {
      digitalWrite(gatePin, HIGH);
      millisPassed = millis() - previousMillis;
      current = (battVolt - shuntVolt) / shuntRes;
      mAh = mAh + (current * 1000.0) * (millisPassed / 3600000.0);
      previousMillis = millis();
 
      //lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(battVolt, 2);
      lcd.print("V   ");
      lcd.print("La ");
      lcd.print(current, 2);
      lcd.print("A");
      lcd.setCursor(0,1);
      lcd.print("Kap: ");
      lcd.print(mAh);
      lcd.print("mAh    ");
      //    lcd.println();
             
      Serial.print(battVolt);
      Serial.println("\t");
      //Serial.print(current);
      //Serial.print("\t");
      //Serial.println(mAh);
       
      delay(interval);
  }
  if(battVolt <= battLow && finished == false){
      digitalWrite(gatePin, LOW);
      finished = true;
      lcd.clear();
      //lcd.backlight();
      lcd.setCursor(0,0);
      lcd.print("ENTLADEN   ");
      lcd.print(battVolt, 2);
      lcd.print("V  ");
      lcd.setCursor(0,1);
      lcd.print("Kap: ");
      lcd.print(mAh);    
      lcd.print("mAh");       
      delay(interval * 2);
  }}  
