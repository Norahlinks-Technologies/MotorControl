#include <Arduino.h>

int dir= 7;
int vr= 6;
int sig = 5;

int ch6 = 9;
int ch5 = 10;
int ch4 = 8;
int ch3 = 11;
int ch2 = 12;
int ch1 = 13;

long int ch6Data;
long int ch5Data;
long int ch4Data;
long int ch3Data;
long int ch2Data;
long int ch1Data;



void setup() 

{
  Serial.begin(9600);
  pinMode(ch1, INPUT);
  pinMode(ch2, INPUT);
  pinMode(ch3, INPUT);
  pinMode(ch4, INPUT);
  pinMode(ch5, INPUT);
  pinMode(ch6, INPUT);


  pinMode(dir, OUTPUT);
  pinMode(vr, OUTPUT);
  pinMode(sig, OUTPUT);

}

void loop() 
{
  ch1Data = pulseIn(ch1, HIGH, 250000);
  ch2Data = pulseIn(ch2, HIGH, 250000);
  ch3Data = pulseIn(ch3, HIGH, 250000);
  ch4Data = pulseIn(ch4, HIGH, 250000);
  ch5Data = pulseIn(ch5, HIGH, 250000);
  ch6Data = pulseIn(ch6, HIGH, 250000);


  Serial.print("channel 1");
  Serial.println(ch1Data);
 
  Serial.print("channel 2");
  Serial.println(ch2Data);

  Serial.print("channel 3");
  Serial.println(ch3Data);

  Serial.print("channel 4");
  Serial.println(ch4Data);

  Serial.print("channel 5");
  Serial.println(ch5Data);

  Serial.print("channel 6");
  Serial.println(ch6Data);

  _delay_ms(500);
}