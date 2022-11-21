#ifndef __ ARMCODE__
#define __ARMCODE__
#include <Arduino.h>
// #define armIN1 A3
// #define armIN2 A4
namespace arm
{
  enum direction_t {extend = (uint8_t) 1u, retract = (uint8_t) 0u};
}
 class ARM
 {
  private:
    uint8_t exPin, retPin, _Direction , _speed;
    arm::direction_t *_direction;
    uint16_t _fastlife { };


  public:
    ARM() = default;
    ARM(const uint8_t &signalPin1, const uint8_t &signalpin2);

    bool extendArm(const uint8_t &fastlife);
   

    bool retractArm(const uint8_t &fastlife);

    bool stop();

 };

















#endif