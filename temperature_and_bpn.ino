#include<LiquidCrystal.h>

int btnPin = 2;
int sigPin = A0;
int tempPin = A1;
int RS = 10, EN = 9;
int count = 0, BPM = 0;
unsigned long beginning, ending;
int d4 = 5, d5 = 6, d6 = 7, d7 = 8;
float tempValue, millivolts, celsius;
LiquidCrystal lcd(RS, EN, d4, d5, d6, d7);

byte customChar1[8] = {0B00000, 0B00000, 0B00011, 0B00111, 0B01111, 0B01111, 0B01111, 0B01111};
byte customChar2[8] = {0B00000, 0B11000, 0B11100, 0B11110, 0B11111, 0B11111, 0B11111, 0B11111};
byte customChar3[8] = {0B00000, 0B00011, 0B00111, 0B01111, 0B11111, 0B11111, 0B11111, 0B11111};
byte customChar4[8] = {0B00000, 0B10000, 0B11000, 0B11100, 0B11110, 0B11110, 0B11110, 0B11110};
byte customChar5[8] = {0B00111, 0B00011, 0B00001, 0B00000, 0B00000, 0B00000, 0B00000, 0B00000};
byte customChar6[8] = {0B11111, 0B11111, 0B11111, 0B11111, 0B01111, 0B00111, 0B00011, 0B00001};
byte customChar7[8] = {0B11111, 0B11111, 0B11111, 0B11111, 0B11110, 0B11100, 0B11000, 0B10000};
byte customChar8[8] = {0B11100, 0B11000, 0B10000, 0B00000, 0B00000, 0B00000, 0B00000, 0B00000};

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(sigPin, INPUT);
  pinMode(tempPin, INPUT);
  pinMode(btnPin, INPUT_PULLUP);
  lcd.createChar(1, customChar1);
  lcd.createChar(2, customChar2);
  lcd.createChar(3, customChar3);
  lcd.createChar(4, customChar4);
  lcd.createChar(5, customChar5);
  lcd.createChar(6, customChar6);
  lcd.createChar(7, customChar7);
  lcd.createChar(8, customChar8);
}

void loop() {
  while(digitalRead(btnPin) > 0);

  beginning = millis();
  ending = beginning + 10000;

  while(millis() <= ending) {
    if(analogRead(sigPin) > 500) {
      count++;
      lcd.setCursor(6, 0);
      lcd.write(byte(1));
      lcd.setCursor(7, 0);
      lcd.write(byte(2));
      lcd.setCursor(8, 0);
      lcd.write(byte(3));
      lcd.setCursor(9, 0);
      lcd.write(byte(4));
      lcd.setCursor(6, 1);
      lcd.write(byte(5));
      lcd.setCursor(7, 1);
      lcd.write(byte(6));
      lcd.setCursor(8, 1);
      lcd.write(byte(7));
      lcd.setCursor(9, 1);
      lcd.write(byte(8));
      while(digitalRead(sigPin));
      lcd.clear();
    }
  }

  BPM = count * 6;
  tempValue = analogRead(tempPin);
  millivolts = (tempValue / 1024.0) * 5000;
  celsius = millivolts / 10;
  lcd.setCursor(0, 0);
  lcd.print("BPM: ");
  lcd.print(BPM);
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(celsius);
  lcd.setCursor(12, 0);
  lcd.write(byte(1));
  lcd.setCursor(13, 0);
  lcd.write(byte(2));
  lcd.setCursor(14, 0);
  lcd.write(byte(3));
  lcd.setCursor(15, 0);
  lcd.write(byte(4));
  lcd.setCursor(12, 1);
  lcd.write(byte(5));
  lcd.setCursor(13, 1);
  lcd.write(byte(6));
  lcd.setCursor(14, 1);
  lcd.write(byte(7));
  lcd.setCursor(15, 1);
  lcd.write(byte(8));
  count = 0;
  BPM = 0;
}
