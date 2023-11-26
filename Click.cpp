#include "Click.h"
#include <Arduino.h>

Click::Click()
{
}

Click::Click(int _clickPin)
{
    clickPin = _clickPin;
    lastChange = millis();
    lastClick = millis();
    state = 0;
    pressed = false;
}

int Click::getState()
{
    if (state == 0)
    {
        return 0;
    }
    else
    {
        int tmp = state;
        state = 0;
        return tmp;
    }
}

void Click::update()
{
    bool isClicked = (1 - digitalRead(clickPin) > 0.5);
    if (isClicked)
    {
        if (!pressed && millis() - lastClick > TIME_INBETWEEN_CLICKS)
        {
            lastChange = millis();
            pressed = true;
        }
    }
    else
    {
        if (pressed)
        {
            unsigned long pressTime = millis() - lastChange;
            if (pressTime > TIME_DOUBLE_CLICK)
            {
                state = 2;
            }
            else
            {
                state = 1;
            }
            lastClick = millis();
            pressed = false;
        }
    }
}

bool Click::isPressed()
{
    return pressed;
}
