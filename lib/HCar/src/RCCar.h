#ifndef __RCCAR_H__
#define __RCCAR_H__
#include <Arduino.h>
#include <RClib.h>
#include <hoverboard.h>

class RCCar
{
    public:

    //Methods:
    RCCar() = default;
    explicit RCCar(HMotor*, HMotor*, HMotor*, HMotor*);

    void moveLeft(const direction_t &, const long &);
    void moveRight(const direction_t &, const long &);
    void moveForwards(const long &);
    void moveBackwards(const long &);
    void stop();
    bool isForward();
    bool isBackward();

    private:

    //Methods:

    //Attributes:
    HMotor *motor1, *motor2, *motor3, *motor4;
    HMotor *pair1 [2], *pair2 [2];
    direction_t direction;
};

#endif
