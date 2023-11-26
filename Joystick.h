#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "Click.h"

class Joystick
{
private:
  int xPin;
  int yPin;
  Click click;
  int offset;

public:
  // Constructor
  Joystick();
  void begin(int xPin, int yPin, int clickPin);

  // Set offset
  void setOffset(int _offset);

  // States Getters
  int getPositionState();
  int getClickState();

  // Raw Data Getters
  float getXPosition();
  float getYPosition();

  // Updated for click
  void updateClick();
};

#endif
