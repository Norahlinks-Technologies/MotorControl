#include <Arduino.h>
#include "hoverboard.h"
#include "RCLib.h"
// #include "RCCar.h"
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

#define _signal_pin4     14 //Red
#define _speed_pin4      15 //Yellow
#define _direction_pin4  16 //White

uint8_t chPins[] { 17, 18, 19, 20, 21, 22 };   //Pins for channels

direction_t currentDir { };

void moveForwards(const uint8_t&);
void moveBackwards(const uint8_t&);
void moveLeft(const uint8_t&);
void moveRight(const uint8_t&);


HMotor motor1 (_signal_pin1, _speed_pin1, _direction_pin1);  //Hoverboard Motor1
HMotor motor2(_signal_pin2, _speed_pin2, _direction_pin2);
HMotor motor3(_signal_pin3, _speed_pin3, _direction_pin3);
HMotor motor4(_signal_pin4, _speed_pin4, _direction_pin4);

// RCCar car(&motor1, &motor2, &motor3, &motor4);                  //Remote controlled car

RC remote (2, chPins);                                    //RC module, using 2 channels connected to pins 3 & 4

long       ch1Data { },
           ch2Data { },
           ch1Ref { },
           ch2Ref { };


void setup()
{
  // remote.init(2, Y, 1, X);

  // Serial.begin(9600);
  motor1.stop();
  motor2.stop();
  motor3.stop();
  motor4.stop();
  ch1Ref = remote.readJoystick(1, X);
  ch2Ref = remote.readJoystick(2, Y);
}

void loop()
{
  ch1Data = remote.readJoystick(1, X);
  ch2Data = remote.readJoystick(2, Y);    //Read the joystick via channel 2, which is the Y axis


    if(ch2Data < ch2Ref)
    {
      ch2Data = abs(ch2Data);           //Make the value of ch2Data positive
      ch2Data = map(ch2Data, 0, 255, 25, 250);
      ch2Data = constrain(ch2Data, 0, 250);
      moveForwards(ch2Data);
    }

    else if((ch2Data == ch2Ref))
    {
      motor1.stop();
      motor2.stop();
      motor3.stop();
      motor4.stop();
    }

    else
    {
      ch2Data = map(ch2Data, 0, 255, 25, 250);
      ch2Data = constrain(ch2Data, 0, 250);
      moveBackwards(ch2Data);
    }

    // if(ch1Data < 0)             //Joystick towards left
    // {
    //   ch1Data = abs(ch1Data);
    //   ch1Data = constrain(ch1Data, 0, 255);

    //   moveLeft(ch1Data);
    // }

    // else if((ch1Data == ch1Ref) && (ch2Data == ch2Ref))      //Joystick at centre
    // {
    //   motor1.stop();
    //   motor2.stop();
    //   motor3.stop();
    //   motor4.stop();
    // }

    // else                          //Joystick towards right
    // {
    //   ch1Data = constrain(ch1Data, 0, 255);

    //   moveRight(ch1Data);
    // }
    delay(250);

  }

  // else
  // {
  //   act1.stop();
  //   act1.extendArm(ch1Data);
  //   act1.retractArm(ch1Data);
  //   act2.stop();
  //   act2.extendArm(ch2Data);
  //   act2.retractArm(ch2Data);
  // }

// }

bool checkSwitch(void)
{
  if (remote.readButton(chPins[2]) > 1000)
    return (true);
  else
    return (false);

}

void moveForwards(const uint8_t& speed)
{
  motor1.move(forward, speed);
  // motor3.move(forward, speed);
  motor2.move(backward, speed);
  // motor4.move(backward, speed);
  currentDir = forward;
}

void moveBackwards(const uint8_t& speed)
{
  motor1.move(backward, speed);
  // motor3.move(backward, speed);
  motor2.move(forward, speed);
  // motor4.move(forward, speed);
  currentDir = backward;
}

void moveLeft(const uint8_t& speed)
{
  motor1.move(!currentDir, 255 - speed);
  motor2.move(currentDir, speed);
  // motor3.move(!currentDir, 255 - speed);
  // motor4.move(currentDir, speed);
}

void moveRight(const uint8_t& speed)
{
  motor1.move(currentDir, speed);
  motor2.move(!currentDir, 255 - speed);
  // motor3.move(currentDir, speed);
  // motor4.move(!currentDir, 255 - speed);
}
