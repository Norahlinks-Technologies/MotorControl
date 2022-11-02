#include <Arduino.h>
#include "hoverboard.h"
#include "RCLib.h"

#define _signal_pin1     5 //Red
#define _speed_pin1      6 //Yellow
#define _direction_pin1  7 //White

#define _signal_pin2     8 //Red
#define _speed_pin2      9 //Yellow
#define _direction_pin2  10 //White

#define _signal_pin3     11 //Red
#define _speed_pin3      12 //Yellow
#define _direction_pin3  13 //White

#define _signal_pin4     A0 //Red
#define _speed_pin4      A1 //Yellow
#define _direction_pin4  A2 //White

uint8_t chPins[2] { 3, 4 };   //Pins for channels



HMotor motor1 (_signal_pin1, _speed_pin1, _direction_pin1);  //Hoverboard Motor
HMotor motor2(_signal_pin2, _speed_pin2, _direction_pin2);
HMotor motor3(_signal_pin3, _speed_pin3, _direction_pin3);
HMotor motor4(_signal_pin4, _speed_pin4, _direction_pin4);

RC remote (2, chPins);                                    //RC module, using 2 channels connected to pins 3 & 4

long       ch1Data { },
           ch2Data { };


void setup()
{
  remote.init(2, Y, 1, X);
  
  // Serial.begin(9600);
  motor1.stop();
  motor2.stop();
  motor3.stop();
  motor4.stop();
}

void loop()
{
  ch2Data = remote.readJoystick(2, Y);    //Read the joystick via channel 2, which is the Y axis
  // ch1Data = remote.readJoystick(1, X);

  Serial.print("Channel 2: \t");
  Serial.println(ch2Data);


  if(ch2Data < 0)
  {
    ch2Data = abs(ch2Data);           //Make the value of ch2Data positive
    ch2Data = constrain(ch2Data, 0, 255);

    motor1.move(forward, ch2Data);
    motor2.move(backward, ch2Data);
    motor3.move(forward, ch2Data);
    motor4.move(backward, ch2Data);
  }

  else if(ch2Data == 0)
  {
    // ch2Data = lowByte(ch2Data);
    motor1.stop();
    motor2.stop();
    motor3.stop();
    motor4.stop();
  }

  else
  {
    ch2Data = constrain(ch2Data, 0, 255);
    motor1.move(backward, ch2Data);
    motor2.move(forward, ch2Data);
    motor3.move(backward, ch2Data);
    motor4.move(forward, ch2Data);
  }

  delay(500);
}
