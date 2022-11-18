#include <Arduino.h>
#include <RClib.h>
#include <hoverboard.h>
#include <RCCar.h>

RCCar::RCCar(HMotor *_motor1, HMotor *_motor2, HMotor *_motor3, HMotor *_motor4)
    :motor1 { _motor1 }, motor2 { _motor2 }, motor3 { _motor3 }, motor4 { _motor4 }, direction { forward }
{
    motor1->stop();
    motor2->stop();
    motor3->stop();
    motor4->stop();
    pair1[0] = motor1;
    pair1[1] = motor3;
    pair2[0] = motor2;
    pair2[1] = motor4;
}

void RCCar::moveForwards(const long &speed)
{
    for(int i = 0; i < 2; ++i)
    {
        pair1[i]->move(backward, speed);
        pair2[i]->move(forward, speed);
    }
    this->direction = forward;
}

void RCCar::moveBackwards(const long &speed)
{
    for(int i = 0; i < 2; ++i)
    {
        pair1[i]->move(forward, speed);
        pair2[i]->move(backward, speed);
    }
    this->direction = backward;
}

void RCCar::moveLeft(const direction_t &direction, const long &speed)
{
    for(int i = 0; i > 2; ++i)
    {
        pair2[i]->move(direction, speed);
        pair1[i]->move(!direction, 255 - speed);
    }
}

void RCCar::moveRight(const direction_t &direction, const long &speed)
{
    for(int i = 0; i < 2; ++i)
    {
        pair1[i]->move(direction, speed);
        pair2[i]->move(!direction, 255 - speed);
    }
}

void RCCar::stop()
{
    for(int i = 0; i < 2; ++i)
    {
        pair1[i]->stop();
        pair2[i]->stop();
    }
}

bool RCCar::isForward()
{
    return ((this->direction == forward) ? true : false );
}

bool RCCar::isBackward()
{
    return ((this->direction == backward) ? true : false );
}
