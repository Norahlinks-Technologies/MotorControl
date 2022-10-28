#include <Arduino.h>
#include "hoverboard.h"


HMotor motor1 (5, 6, 7);
uint8_t ch1 {3}, ch2{4};
uint32_t ch1Data { }, ch2Data { }, speed;


void setup()
{
  Serial.begin(9600);
  for(int i = 3; i < 5; ++i)
    pinMode(i, 0);
}

void loop()
{
  ch1Data = pulseIn(ch1, HIGH, 25000);
  ch2Data = pulseIn(ch2, HIGH, 25000);

  Serial.print("Channel 1:\t");
  Serial.println(ch1Data);
  Serial.println();

  Serial.print("Channel 2:\t");
  Serial.println(ch2Data);
  Serial.println();
  Serial.println();

  delay(2000);
  //TODO:
  //*** 1. Use value of ch1Data and ch2Data to move motors.
  //*** 2. ch1Data moves the motor forwards and backwards.

  // motor1.move(forward, 127);
  // delay(2000);
}
