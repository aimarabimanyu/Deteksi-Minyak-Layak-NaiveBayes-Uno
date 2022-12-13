#include <Arduino.h>

#define s0_color 8        
#define s1_color 9
#define s2_color 10
#define s3_color 11
#define out_color 12
#define  A0_ldr A0

int LDRAnalogValue;
int data=0;

void GetData();

void setup() 
{
  pinMode(s0_color,OUTPUT);
  pinMode(s1_color,OUTPUT);
  pinMode(s2_color,OUTPUT);
  pinMode(s3_color,OUTPUT);
  pinMode(out_color,INPUT);
  pinMode(A0_ldr, INPUT);

  Serial.begin(9600);
   
  digitalWrite(s0_color,HIGH);
  digitalWrite(s1_color,HIGH);
}

void loop()
{
  LDRAnalogValue = analogRead(A0_ldr);
  Serial.print("Intensity=");
  Serial.println(LDRAnalogValue,DEC);

  digitalWrite(s2_color,LOW);
  digitalWrite(s3_color,LOW);
  Serial.print("Red value= "); 
  GetData();

  digitalWrite(s2_color,LOW);
  digitalWrite(s3_color,HIGH);
  Serial.print("Blue value= ");
  GetData();

  digitalWrite(s2_color,HIGH);
  digitalWrite(s3_color,HIGH);
  Serial.print("Green value= ");
  GetData();
  
  Serial.println();

  delay(2000);
}

void GetData()
{
  data=pulseIn(out_color,LOW);       //here we wait until "out" go LOW, we start measuring the duration and stops when "out" is HIGH again
  Serial.print(data);          //it's a time duration measured, which is related to frequency as the sensor gives a frequency depending on the color
  Serial.print("\t");          //The higher the frequency the lower the duration
  delay(20);
}
