#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "classifier.h"

#define s0_color 8        
#define s1_color 9
#define s2_color 10
#define s3_color 11
#define out_color 12
#define A0_ldr A0

Eloquent::ML::Port::GaussianNB model;
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  Serial.begin(9600);

  pinMode(s0_color,OUTPUT);
  pinMode(s1_color,OUTPUT);
  pinMode(s2_color,OUTPUT);
  pinMode(s3_color,OUTPUT);
  pinMode(out_color,INPUT);
  pinMode(A0_ldr, INPUT);

  digitalWrite(s0_color,HIGH);
  digitalWrite(s1_color,HIGH);

  lcd.init();
	lcd.backlight();
	lcd.clear();
}

void loop() {
  float Sample[2] = {};

  Sample[0] = analogRead(A0_ldr);
  Serial.print("Intensity=");
  Serial.println(Sample[0]);

  digitalWrite(s2_color,LOW);
  digitalWrite(s3_color,LOW);
  Sample[1] =pulseIn(out_color,LOW);
  Serial.print("Red value= ");
  Serial.println(Sample[1]); 

  int predict = model.predict(Sample);
  Serial.print("Predict= ");
  Serial.println(predict);

  if (predict == 0) {
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("Layak");
  }
  else if (predict == 1) {
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Tidak Layak");
  }

  Serial.println();
  Serial.println();

  delay(2000);
}
