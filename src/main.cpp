#include <Arduino.h>
#include "hoverboard.h"
#include "RCLib.h"
#include "RCCar.h"
#include "armCode.h"

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
#define extendPin1       18
#define retractPin1      19
#define extendPin2       20
#define retractPin2      21


enum control_t { _ARM = (bool) 0, _CAR = (bool) 1 };

uint8_t chPins[] { 3, 4, 14, 15, 16, 17 };   //Pins for channels

control_t control { _CAR };
bool checkSwitch(void);



HMotor motor1 (_signal_pin1, _speed_pin1, _direction_pin1);  //Hoverboard Motor1
HMotor motor2(_signal_pin2, _speed_pin2, _direction_pin2);
HMotor motor3(_signal_pin3, _speed_pin3, _direction_pin3);
HMotor motor4(_signal_pin4, _speed_pin4, _direction_pin4);

RCCar car(&motor1, &motor2, &motor3, &motor4);                  //Remote controlled car

RC remote (2, chPins);                                    //RC module, using 2 channels connected to pins 3 & 4

ARM act1(extendPin1, retractPin1);
ARM act2(extendPin1, retractPin1);


long       ch1Data { },
           ch2Data { },
           ch4Data { },
           ch5Data { },
           ch6Data { },
           ch1Ref { },
           ch2Ref { };


void setup()
{
  // remote.init(2, Y, 1, X);

  // Serial.begin(9600);
  car.stop();
  ch1Ref = remote.readJoystick(1, X);
  ch2Ref = remote.readJoystick(2, Y);
}

void loop()
{
  ch1Data = remote.readJoystick(1, X);
  ch2Data = remote.readJoystick(2, Y);    //Read the joystick via channel 2, which is the Y axis

  if (checkSwitch() == true)
  {
    control = (control_t) !control;
  }

  if(control == _CAR)
  {
    if(ch2Data < 0)
    {
      ch2Data = abs(ch2Data);           //Make the value of ch2Data positive
      ch2Data = constrain(ch2Data, 0, 255);

      car.moveForwards(ch2Data);
    }

    else if((ch2Data == ch2Ref) && (ch1Data == ch1Ref))
    {
      car.stop();
    }

    else
    {
      ch2Data = constrain(ch2Data, 0, 255);
      car.moveBackwards(ch2Data);
    }

    if(ch1Data < 0)             //Joystick towards left
    {
      ch1Data = abs(ch1Data);
      ch1Data = constrain(ch1Data, 0, 255);

      if(car.isForward())
        car.moveLeft(forward, ch1Data);

      else if(car.isBackward())
        car.moveLeft(backward, ch1Data);

    }

    else if((ch1Data == ch1Ref) && (ch2Data == ch2Ref))      //Joystick at centre
    {
      car.stop();
    }

    else                          //Joystick towards right
    {
      ch1Data = constrain(ch1Data, 0, 255);

      if(car.isForward())
        car.moveRight(forward, ch1Data);

      else if(car.isBackward())
        car.moveRight(backward, ch1Data);
    }
    delay(250);
    
  }

  else
  {
    act1.stop();
    act1.extendArm(ch1Data);
    act1.retractArm(ch1Data);
    act2.stop();
    act2.extendArm(ch2Data);
    act2.retractArm(ch2Data);
  }

}

bool checkSwitch(void)
{
  if (remote.readButton(chPins[2]) > 1000)
    return (true);
  else
    return (false);

}