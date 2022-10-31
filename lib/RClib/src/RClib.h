#ifndef __RCLIB_H__
#define __RCLIB_H__

//X and Y values of joystick(s) on remote control, measured using pulseIn()
#define XMIN    1033
#define XMAX    2027
#define YMIN    983
#define YMAX    1977


#include <Arduino.h>

namespace RClib
{
    template <typename T>
        const int32_t &mapX(const uint8_t &num, const T &rem, const uint32_t &outMin, const uint32_t &outMax)
        {
            static int32_t temp { };
            temp = (num - rem.xMin) * (outMax - outMin) / (rem.xMax - rem.xMin) + outMin;
            return (temp);
        }


    template <typename T>
        const int32_t &mapY(const uint8_t &num, const T &rem, const uint32_t &outMin, const uint32_t &outMax)
        {
            static int32_t temp { };
            temp = (num - rem.xMin) * (outMax - outMin) / (rem.xMax - rem.xMin) + outMin;
            return (temp);
        }
}


enum axis_t { X = 0, Y = 1 };

class RC
{
   public:
    //Constructors:
    RC() = default;

    explicit RC(const uint8_t &numChannels, const uint8_t *channelPins);        //To use default X and Y values

    explicit RC(const uint8_t &numChannels, const uint8_t *channelPins, const uint8_t &xmin, const uint8_t &xmax, const uint8_t &ymin, const uint8_t &ymax);                    //To define X and Y values

    ~RC();

    //Methods:
    int32_t readJoystick(const uint8_t &ch, const axis_t &axis);
    uint16_t readButton(const uint8_t &ch);

    template <typename T>
    friend const int32_t& RClib::mapX(const uint8_t &num, T &rem, const uint32_t &outMin, const uint32_t &outMax);
    template <typename T>
    friend const int32_t& RClib::mapY(const uint8_t &num, T &rem, const uint32_t &outMin, const uint32_t &outMax);

    uint16_t xMin, xMax, yMin, yMax;


    private:
    //Attributes:
    uint8_t *chPins;
};

#endif
