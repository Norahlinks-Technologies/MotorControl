#include <Arduino.h>
#include "hoverboard.h"
#include "RCLib.h"

#define _signal     5 //Green
#define _speed      6 //Yellow
#define _direction  7 //White

uint8_t ch [] = { 3, 4 };   //Pins for channels



HMotor motor1 (_signal, _speed, _direction);    //Motor
RC remote (2, ch);                              //RC module

uint8_t     speed { };

int32_t    ch1Data { },
           ch2Data { };


void setup()
{
  Serial.begin(9600);
  motor1.stop();
}

void loop()
{
  ch2Data = remote.readJoystick(2, Y);    //Read the joystick via channel 2, which is the Y axis
  Serial.print("Channel 2: \t");
  Serial.println(ch2Data);

  if(ch2Data < 0)
  {
    ch2Data = abs(ch2Data);           //Make the value of ch2Data positive if negative

    motor1.move(backward, ch2Data);
  }

  else if(ch2Data == 0)
  {
    motor1.stop();
  }

  else
  {
    motor1.move(forward, ch2Data);
  }

  delay(500);
}
