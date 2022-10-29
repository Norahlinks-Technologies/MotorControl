#include <Arduino.h>
#include "hoverboard.h"
#define _signal 5
#define _speed 6
#define _direction 7


HMotor motor1 (_signal, _speed, _direction); //contructor from class HMotor
uint8_t ch1 {3}, ch2{4},  speed { };
uint32_t ch1Data { }, ch2Data { };


void setup()
{
  Serial.begin(9600);
  for(int i = 3; i < 5; ++i)
    pinMode(i, 0);
  /* Aternatively 
    pinMode(3,INPUT);
    pinMode(4, INPUT);
  
  */  
}

void loop()
{
  ch1Data = pulseIn(ch1, HIGH, 25000); // check state and value of ch1
  Serial.print("Channel 1:\t");
  Serial.println(ch1Data); // prints the value to the screen
  Serial.println();
  delay(200);

  ch2Data = pulseIn(ch2, HIGH, 25000);// check state and value of ch2
  Serial.print("Channel 2:\t");
  Serial.println(ch2Data); // prints the value to the screen
  Serial.println();
  Serial.println();
  delay(200);
  // delay(2000);

  speed = scaleCh2(ch2Data);

  motor1.move(forward, speed);
  delay(2000);
}
