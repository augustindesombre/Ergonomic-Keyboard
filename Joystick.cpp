#include "Joystick.h"
#include <Arduino.h>

Joystick::Joystick()
{
}

void Joystick::begin(int _xPin, int _yPin, int _clickPin)
{
  xPin = _xPin;
  yPin = _yPin;
  click = Click(_clickPin);
  offset = 0;

  pinMode(_xPin, INPUT);
  pinMode(_yPin, INPUT);
  pinMode(_clickPin, INPUT);
}

void Joystick::setOffset(int _offset)
{
  offset = _offset;
}

int Joystick::getPositionState()
{
  /* Returns a int corresponding to the sector in which the joystick is.
   */
  float radiusThreshold = 0.9;

  float dist2Center = sqrt(pow(getXPosition(), 2) + pow(getYPosition(), 2));

  if (dist2Center < radiusThreshold)
  {
    return 0;
  }

  float angle = atan2f(getXPosition(), getYPosition()); // between -pi and +pi
  angle = (angle + PI - PI / 8);                        // Between -PI/8 and +15*PI/8
  int state;
  if (angle < 0)
  { // Particular case of circle folding back on itself
    state = 8;
  }
  else
  {
    state = int((((angle) / (2 * PI)) * 8)) + 1; // between 1 (included) and 8 (included)
  }

  state = 9 - state; // to change direction of rotation (clockwise)
  state = (state + 7 - offset) % 8 + 1;
  return state;
}

int Joystick::getClickState()
{
  return this->click.getState();
}

float Joystick::getXPosition()
{
  /* Returns x value of Joystick between 0 and 1
   */
  float x = analogRead(xPin);
  return (x - 511) / 511;
}

float Joystick::getYPosition()
{
  /* Returns y value of Joystick between 0 and 1
   */
  float y = analogRead(yPin);
  return (y - 511) / 511;
}

void Joystick::updateClick()
{
  click.update();
}