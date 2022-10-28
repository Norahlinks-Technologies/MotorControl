#ifndef __HOVERBOARD_H__
#define __HOVERBOARD_H__
#include <Arduino.h>

enum direction_t { forward = (uint8_t) 1u, backward = (uint8_t) 0u };

class HMotor
{
    public:
    //Constructors:
    HMotor() = default;
    HMotor(const uint8_t &signalPin, const uint8_t &speedPin, const uint8_t &directionPin);

    //Methods:
    bool move(const direction_t &direction, const uint8_t &speed);

    private:
    //Attributes:
    #ifndef DIFF
    #define DIFF 1
    #endif
    uint8_t _speed { }, _signal { }, _direction { };
    /* Variables to control speed:  */ uint8_t var1 { }, var2 {DIFF};
    direction_t _Direction { };
};

#endif
