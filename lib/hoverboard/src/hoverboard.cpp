#include <Arduino.h>
#include "hoverboard.h"

HMotor::HMotor(const uint8_t &signalPin, const uint8_t &speedPin, const uint8_t &directionPin)
        : _signal{signalPin}, _speed{speedPin}, _direction{directionPin}
{
    pinMode(_signal, 1);
    pinMode(_direction, 1);
    pinMode(_speed, 1);
}

bool HMotor::move(const direction_t &direction, const uint8_t &speed)
{
    _Direction = direction;
    if(speed<0 || speed > 255)
        return 0;

    digitalWrite(_signal, 1);
    digitalWrite(_direction, _Direction);


    analogWrite(_speed, speed);
    // var1 += var2;
    // delay(100);
    // if((var1 == 255 || var1 == 0))
    //     var2 = -var2;

    return 1;
}


