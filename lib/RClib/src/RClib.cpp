#include <Arduino.h>
#include "RClib.h"


RC::RC(const uint8_t &numChannels, const uint8_t *channelPins)
  :xMin {XMIN}, xMax {XMAX}, yMin {YMIN}, yMax {YMAX}, chPins { new uint8_t[numChannels]}
{
  for(int i = 0; i < numChannels; ++i)
  {
    chPins[i] = channelPins [i];
    pinMode(chPins[i], INPUT);
  }
}

RC::RC(const uint8_t &numChannels, const uint8_t *channelPins, const uint8_t &xmin, const uint8_t &xmax, const uint8_t &ymin, const uint8_t &ymax)
  :xMin {xmin}, xMax {xmax}, yMin {ymin}, yMax {ymax}, chPins { new uint8_t[numChannels]}
{
  for(int i = 0; i < numChannels; ++i)
  {
    chPins[i] = channelPins [i];
    pinMode(chPins[i], INPUT);
  }
}
RC::~RC()
{
  delete chPins;
  chPins = nullptr;
}

long RC::readJoystick(const uint8_t &ch, const axis_t &axis)
{
  using namespace RClib;
  static long temp;
  temp = pulseIn(chPins[ch-1], HIGH, 25000);
  delay(100);

  if(axis == X)
  {
    temp = (RClib::mapX(temp, this, -256, 255));

    return (temp);
  }
  else
  {
    temp = (RClib::mapY(temp, this, -256, 255));

    return (temp);
  }
}

uint16_t RC::readButton(const uint8_t &ch)
{
  return(pulseIn(chPins[ch-1], HIGH, 25000));
}
