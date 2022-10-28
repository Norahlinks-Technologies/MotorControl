#include <Arduino.h>
#include "hoverboard.h"


HMotor motor1 (5, 6, 7);
uint8_t ch1 {4}, ch2{3};
uint32_t ch1Data { }, ch2Data { }, speed;


void setup()
{
  for(int i = 3; i < 5; ++i)
    pinMode(i, 0);
}

void loop()
{
  ch1Data = pulseIn(ch1, HIGH, 25000);
  ch2Data = pulseIn(ch2, HIGH, 25000);

  //TODO:
  //*** 1. Use value of ch1Data and ch2Data to move motors.
  //*** 2. ch1Data moves the motor forwards and backwards.

  motor1.move(forward, 127);
  delay(2000);
}
