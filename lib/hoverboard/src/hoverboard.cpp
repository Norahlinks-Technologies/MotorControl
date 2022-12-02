#include <Arduino.h>
#include "hoverboard.h"

HMotor::HMotor(const uint8_t &signalPin, const uint8_t &speedPin, const uint8_t &directionPin)
        :  _speed{speedPin}, _signal{signalPin}, _direction{directionPin}
{
    pinMode(_signal, 1);
    pinMode(_direction, 1);
    pinMode(_speed, 1);
}

bool HMotor::move(const direction_t &Direction, const uint8_t &speed)
{
    if(speed < 0 || speed > 255)
        return 0;

    digitalWrite(_signal, 1);
    digitalWrite(_direction, (int) Direction);


    analogWrite(_speed, speed);

    return 1;
}

HMotor::~HMotor()
{

}


void HMotor::stop()
{
    digitalWrite(_signal, 0);
    analogWrite(_speed, 0);
}
