#include <Arduino.h>
#include "hoverboard.h"
#include "RCLib.h"

#define _signal_pin     5 //Green
#define _speed_pin      6 //Yellow
#define _direction_pin  7 //White

uint8_t chPins []= { 3, 4 };   //Pins for channels



HMotor motor1 (_signal_pin, _speed_pin, _direction_pin);    //Hoverboard Motor
RC remote (2, chPins);                                      //RC module, using 2 channels connected to pins 3 & 4

long       ch1Data { },
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
    ch2Data = abs(ch2Data);           //Make the value of ch2Data positive
    ch2Data = constrain(ch2Data, 0, 255);

    motor1.move(backward, ch2Data);
  }

  else if(ch2Data == 0)
  {
    ch2Data = lowByte(ch2Data);
    motor1.stop();
  }

  else
  {
    ch2Data = constrain(ch2Data, 0, 255);
    motor1.move(forward, ch2Data);
  }

  delay(500);
}
