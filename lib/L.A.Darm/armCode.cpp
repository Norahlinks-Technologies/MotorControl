#include "armCode.h"
#include "RClib.h"


ARM::ARM(const uint8_t &signalPin1, const uint8_t &signalPin2)
: exPin {signalPin1}, retPin {signalPin2}
{
 pinMode(exPin, OUTPUT);
 pinMode(retPin, OUTPUT);
}


bool ARM::stop()
{
    digitalWrite(exPin, LOW);
    digitalWrite(retPin, LOW);
}


bool ARM:: extendArm(const uint8_t &fastlife)
{
   // uint16_t _fastlife {constrain(pulseIn(chPins[ch-1], HIGH, 25000), 890, 1850) };
    *_direction = arm::extend;
    _fastlife == (fastlife > 0) ? map(fastlife, -256, 255, 0, 255) : 0;
    
    if(_fastlife)
        {
        analogWrite(exPin, map(_fastlife, 0, 255, 51, 255 ));
        analogWrite(retPin, 0);
        return 1;
         }

    else
    {
        stop();
        return 0;
    }
}

bool ARM::retractArm(const uint8_t &fastlife)
{
// uint16_t _fastlife {constrain(pulseIn(chPins[ch-1], HIGH, 25000), 890, 1850) };
    *_direction = arm::retract;
    _fastlife == (fastlife < 0) ? map(fastlife, -256, 255, 0, 255) : 0;
    
    if(_fastlife)
        {
        analogWrite(exPin, 0);
        analogWrite(retPin, map(_fastlife, 255, 0, 51, 255 ));
        return 1;
         }

    else
    {
        stop();
        return 0;
    }
}
