#ifndef __RCLIB_H__
#define __RCLIB_H__

//X and Y values of joystick(s) on remote control, measured using pulseIn()
#define XMIN    1034
#define XMAX    2028
#define YMIN    984
#define YMAX    1978


#include <Arduino.h>

using ulong = unsigned long;
namespace RClib
{
    template <typename T>
        const long &mapX(const long &num, const T *rem, const long &outMin, const long &outMax)
        {
            static long temp { };
            temp = (num - rem->xMin) * (outMax - outMin) / (rem->xMax - rem->xMin) + outMin;
            return (temp);
        }


    template <typename T>
        const long &mapY(const long &num, const T *rem, const long &outMin, const long &outMax)
        {
            static long temp { };
            temp = (num - rem->yMin) * (outMax - outMin) / (rem->yMax - rem->yMin) + outMin;
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
    long readJoystick(const uint8_t &ch, const axis_t &axis);
    uint16_t readButton(const uint8_t &ch);

    template <typename T>
    friend const long& RClib::mapX(const uint8_t &num, T &rem, const long &outMin, const long &outMax);
    template <typename T>
    friend const long& RClib::mapY(const uint8_t &num, T &rem, const long &outMin, const long &outMax);

    uint16_t xMin, xMax, yMin, yMax;


    private:
    //Attributes:
    uint8_t *chPins;
};

#endif
