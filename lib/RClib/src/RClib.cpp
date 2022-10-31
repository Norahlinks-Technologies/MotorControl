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

int32_t RC::readJoystick(const uint8_t &ch, const axis_t &axis)
{
  using namespace RClib;
  static auto temp = pulseIn(chPins[ch-1], HIGH, 25000);
  delay(100);

  if(axis == X)
    return RClib::mapX(temp, *this, -255, 255);
  else
    return RClib::mapY(temp, *this, -255, 255);
}

uint16_t RC::readButton(const uint8_t &ch)
{
  return(pulseIn(chPins[ch-1], HIGH, 25000));
}
