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

void RC::xMIN(const uint8_t &chnum)
{
    const long temp1 = pulseIn(chPins[chnum-1], HIGH, 25000);
    delay(200);

    const long temp2 = pulseIn(chPins[chnum-1], HIGH, 25000);
    delay(200);
    if (temp1 == temp2)
     {
      this->xMin = ((temp1+temp2)/2);
     }
    else
     {
      const long temp3 = pulseIn(chPins[chnum-1], HIGH, 25000);
      this->xMin  = ((temp1+ temp2+temp3)/3);
     }  
}

void RC::xMAX(const uint8_t &chnum)
{
    const long temp1 = pulseIn(chPins[chnum-1], HIGH, 25000);
    delay(200);

    const long temp2 = pulseIn(chPins[chnum-1], HIGH, 25000);
    delay(200);
    if (temp1 == temp2)
     {
      this->xMax = ((temp1+temp2)/2);
     }
    else
     {
      const long temp3 = pulseIn(chPins[chnum-1], HIGH, 25000);
      this->xMax  = ((temp1+ temp2+temp3)/3);
     }
}

void RC::yMIN(const uint8_t &chnum)
{
    const long temp1 = pulseIn(chPins[chnum-1], HIGH, 25000);
    delay(200);

    const long temp2 = pulseIn(chPins[chnum-1], HIGH, 25000);
    delay(200);
    if (temp1 == temp2)
     {
      this-> yMin = ((temp1+temp2)/2);
     }
    else
     {
      const long temp3 = pulseIn(chPins[chnum-1], HIGH, 25000);
      this-> yMin  = ((temp1+ temp2+temp3)/3);
     }
}

void RC::yMAX(const uint8_t &chnum)
{
    const long temp1 = pulseIn(chPdigitalWrite (13, STATE);
      delay(500);ins[chnum-1], HIGH, 25000);
    delay(200);

    const long temp2 = pulseIn(chPins[chnum-1], HIGH, 25000);
    delay(200);
    if (temp1 == temp2)
     {
      this-> yMax = ((temp1+temp2)/2);
     }
    else
     {
      const long temp3 = pulseIn(chPins[chnum-1], HIGH, 25000);
      this-> yMax  = ((temp1+ temp2+temp3)/3);
     } 
}

void RC::init(const uint8_t &chnum1, axis_t axis1, const uint8_t &chnum2, axis_t axis2)
{
  pinMode(13, OUTPUT);
  toggle(3);

  if(axis1  == X)
    {
      xMIN(chnum1);
      toggle(3);
      xMAX(chnum1);
      toggle(3);
      yMAX(chnum2);
      toggle(3);
      yMIN(chnum2);
      toggle(3);
    }
    
    else
    {
      yMAX(chnum1);
      toggle(3);
      yMIN(chnum1);
      toggle(3);
      xMIN(chnum2);
      toggle(3);
      xMAX(chnum2);
      toggle(3);
    }

}

void RC::toggle(uint8_t times)
{
  uint8_t STATE = 1;
  for (size_t i = 0; i< times; i++)
   {
      digitalWrite (13, STATE);
      delay(500);
      digitalWrite (13, !STATE);
      delay(500);
   }

}